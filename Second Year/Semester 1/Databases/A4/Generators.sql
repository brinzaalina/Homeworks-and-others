-- generate a random string
GO

IF EXISTS (SELECT [name] FROM sys.objects 
            WHERE object_id = OBJECT_ID('generateRandomString'))
BEGIN
   DROP PROCEDURE generateRandomString;
END

IF EXISTS (SELECT [name] FROM sys.objects
			WHERE object_id = OBJECT_ID('generateRandomDataForTable'))
BEGIN
	DROP PROCEDURE generateRandomDataForTable
END

--procedure to generate a random string with a limited length
GO 
CREATE OR ALTER PROCEDURE generateRandomString @stringValue VARCHAR(10) OUTPUT AS
BEGIN
	DECLARE @length INT
	DECLARE @charPool VARCHAR(55)
	DECLARE @charPoolLength INT
	SET @charPool = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
	SET @charPoolLength = LEN(@charPool)
	SET @length = FLOOR(RAND() * 10 + 5)
	SET @stringValue = ''
	WHILE @length > 0
	BEGIN
		SET @stringValue = @stringValue + SUBSTRING(@charPool, CONVERT(INT, RAND() * @charPoolLength) + 1, 1)
		SET @length = @length - 1
	END
END

-- generate random data for a table

GO
CREATE OR ALTER PROCEDURE generateRandomDataForTable @tableName VARCHAR(50), @numberOfRows INT AS
BEGIN
	-- create a cursor to iterate through the names of the column and their types
	DECLARE dataCursor SCROLL CURSOR FOR
		SELECT COLUMN_NAME, DATA_TYPE
		FROM INFORMATION_SCHEMA.COLUMNS
		WHERE TABLE_NAME = @tableName
		ORDER by ORDINAL_POSITION

	-- query for the insert in tables
	DECLARE @insertQuery VARCHAR(MAX)

	DECLARE @columnName VARCHAR(200)
	DECLARE @dataType VARCHAR(10)
	DECLARE @intValue INT
	DECLARE @stringValue VARCHAR(50)
	DECLARE @checkIfPKQuery NVARCHAR(2000)
	DECLARE @hasPK INT

	OPEN dataCursor

	WHILE @numberOfRows > 0
	BEGIN
		SET @hasPK = 0
		SET @insertQuery = 'INSERT INTO ' + @tableName + ' VALUES('
		SET @checkIfPKQuery = N'SELECT @outputPK = COUNT(*) FROM ' + @tableName + ' WHERE '
		FETCH FIRST FROM dataCursor INTO @columnName, @dataType
		WHILE @@FETCH_STATUS = 0
		BEGIN
			IF COLUMNPROPERTY(OBJECT_ID(@tableName), @columnName, 'IsIdentity') = 0
			BEGIN
				-- check if the current column has a foreign key property and if it has, take its values from the referenced table
				IF EXISTS(
					SELECT *
					FROM INFORMATION_SCHEMA.CONSTRAINT_COLUMN_USAGE C
					WHERE C.CONSTRAINT_NAME like 'FK%' AND @columnName = C.COLUMN_NAME AND @tableName = C.TABLE_NAME)
					BEGIN
						-- get the name of the referenced table and the name of the referenced column
						DECLARE @referencedTable VARCHAR(50)
						DECLARE @referencedColumn VARCHAR(50)
						DECLARE @result TABLE([tableName] VARCHAR(50), [columnName] VARCHAR(50))
						INSERT INTO @result SELECT OBJECT_NAME (f.referenced_object_id) AS referenced_table_name,
						COL_NAME(fc.referenced_object_id, fc.referenced_column_id) AS referenced_column_name
						FROM sys.foreign_keys AS f
						INNER JOIN sys.foreign_key_columns AS fc ON f.object_id = fc.constraint_object_id
						WHERE fc.parent_object_id = OBJECT_ID(@tableName) AND COL_NAME(fc.parent_object_id, fc.parent_column_id) = @columnName

						SET @referencedTable = (SELECT TOP 1 [tableName] FROM @result)
						SET @referencedColumn = (SELECT TOP 1 [columnName] FROM @result)
						
						-- empty the table, otherwise it will always have at the top the first table and column found
						DELETE FROM @result

						-- int case
						IF @dataType = 'int'
							BEGIN
								-- get a random value from the referenced table
								DECLARE @getRandomFK NVARCHAR(1000)
								SET @getRandomFK = N'SELECT TOP 1 @intValue = [' + @referencedColumn + '] FROM ' + @referencedTable + ' ORDER BY NEWID()'
								EXEC sp_executesql @getRandomFK, N'@intValue INT OUTPUT', @intValue OUTPUT
								SET @insertQuery = @insertQuery + CAST(@intValue AS NVARCHAR(10)) + ','
							END
						ELSE
							-- string case
							IF @dataType = 'varchar'
								BEGIN
									-- get a random value from the values in the referenced table
									DECLARE @getStringQuery NVARCHAR(200)
									SET @getStringQuery = N'SELECT TOP 1 @stringValue = ['  + @referencedColumn + '] FROM ' + @referencedTable + ' T WHERE ' +
									@columnName + ' = T.' + @columnName + ' ORDER BY NEWID()'
									EXEC sp_executesql @getStringQuery, N'@stringValue VARCHAR(50) OUTPUT', @stringValue OUTPUT
									SET @insertQuery = @insertQuery + '''' + @stringValue + ''','
								END
					END
				ELSE
					-- not a foreign key, does not depend on another table
					BEGIN
						IF @dataType = 'int'
							BEGIN
								-- generate a random number
								SET @intValue = FLOOR(RAND() * 1000) + 1
								SET @insertQuery = @insertQuery + CAST(@intValue AS NVARCHAR(10)) + ','
							END
						ELSE
							IF @dataType = 'varchar'
								BEGIN
									-- generate a random string
									EXEC generateRandomString @stringValue OUTPUT
									SET @insertQuery = @insertQuery + '''' + @stringValue + '''' + ','
								END
							ELSE
								BEGIN
									SET @insertQuery = @insertQuery + 'NULL' + ','
								END
					END

				-- if the column has a primary key, create a query t check its validity
				-- this will also check for multicolumn primary keys
				IF EXISTS(
					SELECT *
					FROM INFORMATION_SCHEMA.CONSTRAINT_COLUMN_USAGE
					WHERE TABLE_NAME = @tableName AND COLUMN_NAME = @columnName AND CONSTRAINT_NAME LIKE 'PK%')
					BEGIN
						SET @hasPK = 1
						IF @dataType = 'varchar'
							BEGIN
								SET @checkIfPKQuery = @checkIfPKQuery + @columnName + '=''' + @stringValue + ''' AND '
							END
						IF @dataType = 'int'
							BEGIN
								SET @checkIfPKQuery = @checkIfPKQuery + @columnName + '=' + CAST(@intValue AS VARCHAR(10)) + ' AND '
							END
					END
			END
			FETCH NEXT FROM dataCursor INTO @columnName, @dataType
		END
		-- insert only if the primary key is valid
		IF @hasPK = 1
			BEGIN
				SET @checkIfPKQuery = LEFT(@checkIfPKQuery, LEN(@checkIfPKQuery) - 4)
				DECLARE @outputPK INT
				EXEC sp_executesql @checkIfPKQuery, N'@outputPK INT OUTPUT', @outputPK OUTPUT
				IF @outputPK = NULL OR @outputPK = 0
					BEGIN
						SET @insertQuery = LEFT(@insertQuery, LEN(@insertQuery) - 1) + ')'
						EXEC (@insertQuery)
						SET @numberOfRows = @numberOfRows - 1
					END
			END
		ELSE
			-- in this case there is no primary key
			BEGIN 
				SET @insertQuery = LEFT(@insertQuery, LEN(@insertQuery) - 1) + ')'
				EXEC (@insertQuery)
				SET @numberOfRows = @numberOfRows - 1
			END
	END
	CLOSE dataCursor
	DEALLOCATE dataCursor
END
