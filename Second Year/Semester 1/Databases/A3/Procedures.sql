USE Music_Production_Company;

-- modify the type of a column
GO
CREATE OR ALTER PROCEDURE setFanPercentageFromFanOfSingerDecimal 
AS
    ALTER TABLE Fan_of_singer ALTER COLUMN fan_percentage DECIMAL(4,2)

GO
CREATE OR ALTER PROCEDURE setFanPercentageFromFanOfSingerInt
AS
	ALTER TABLE Fan_of_singer ALTER COLUMN fan_percentage INT


-- add / remove a column
GO
CREATE OR ALTER PROCEDURE addAuthorNameToReview 
AS
	ALTER TABLE Review ADD author_name VARCHAR(100)

GO
CREATE OR ALTER PROCEDURE removeAuthorNameFromReview
AS
	ALTER TABLE Review DROP COLUMN author_name


-- add/remove a DEFAULT constraint
GO
CREATE OR ALTER PROCEDURE addDefaultToExperienceFromProducer
AS
	ALTER TABLE Producer ADD CONSTRAINT default_exp DEFAULT(0) FOR experience

GO
CREATE OR ALTER PROCEDURE removeDefaultFromExperienceFromProducer
AS
	ALTER TABLE Producer DROP CONSTRAINT default_exp


-- create/drop a table
GO
CREATE OR ALTER PROCEDURE addEmployee 
AS
	CREATE TABLE Employee (
		employee_id INT,
		employee_name VARCHAR(100) NOT NULL,
		employee_role VARCHAR(50) NOT NULL,
		salary INT,
		CONSTRAINT EMPLOYEE_PRIMARY_KEY PRIMARY KEY(employee_id),
		manager_id INT NOT NULL
	)

GO 
CREATE OR ALTER PROCEDURE dropEmployee
AS
	DROP TABLE Employee


-- add/remove a primary key
GO
CREATE OR ALTER PROCEDURE addRoleAndNamePrimaryKeyEmployee
AS
	ALTER TABLE Employee
		DROP CONSTRAINT EMPLOYEE_PRIMARY_KEY
	ALTER TABLE Employee
		ADD CONSTRAINT EMPLOYEE_PRIMARY_KEY PRIMARY KEY(employee_name, employee_role)

GO 
CREATE OR ALTER PROCEDURE removeRoleAndNamePrimaryKeyEmployee
AS
	ALTER TABLE Employee
		DROP CONSTRAINT EMPLOYEE_PRIMARY_KEY
	ALTER TABLE Employee
		ADD CONSTRAINT EMPLOYEE_PRIMARY_KEY PRIMARY KEY(employee_id)


-- add/remove a candidate key
GO
CREATE OR ALTER PROCEDURE newCandidateKeyFan 
AS	
	ALTER TABLE Fan
		ADD CONSTRAINT FAN_CANDIDATE_KEY UNIQUE(fan_name, fan_age, fan_Country)

GO
CREATE OR ALTER PROCEDURE removeCandidateKeyFan
AS
	ALTER TABLE Fan
		DROP CONSTRAINT FAN_CANDIDATE_KEY


-- add / remove a foreign key
GO
CREATE OR ALTER PROCEDURE newForeignKeyEmployee 
AS
	ALTER TABLE Employee
		ADD CONSTRAINT EMPLOYEE_FOREIGN_KEY FOREIGN KEY(manager_id) REFERENCES Manager(manager_id)

GO
CREATE OR ALTER PROCEDURE removeForeignKeyEmployee
AS
	ALTER TABLE Employee
		DROP CONSTRAINT EMPLOYEE_FOREIGN_KEY


-- a table that contains the current version of the database schema

CREATE TABLE versionTable (
	version INT
)

INSERT INTO versionTable 
VALUES
	(1) -- this is the initial version


-- a table that contains the initial version, the version after the execution of the procedure and the procedure that changes the table in this way
CREATE TABLE procedureTable (
	initial_version INT,
	final_version INT,
	procedure_name VARCHAR(MAX),
	PRIMARY KEY (initial_version, final_version)
)

INSERT INTO procedureTable
VALUES
	(1, 2, 'setFanPercentageFromFanOfSingerDecimal'),
	(2, 1, 'setFanPercentageFromFanOfSingerInt'),
	(2, 3, 'addAuthorNameToReview'), 
	(3, 2, 'removeAuthorNameFromReview'),
	(3, 4, 'addDefaultToExperienceFromProducer'),
	(4, 3, 'removeDefaultFromExperienceFromProducer'),
	(4, 5, 'addEmployee'),
	(5, 4, 'dropEmployee'),
	(5, 6, 'addRoleAndNamePrimaryKeyEmployee'),
	(6, 5, 'removeRoleAndNamePrimaryKeyEmployee'),
	(6, 7, 'newCandidateKeyFan'),
	(7, 6, 'removeCandidateKeyFan'),
	(7, 8, 'newForeignKeyEmployee'),
	(8, 7, 'removeForeignKeyEmployee')


-- procedure to bring the database to the specified version
GO
CREATE OR ALTER PROCEDURE goToVersion(@newVersion INT) 
AS
	DECLARE @current_version INT
	DECLARE @procedureName VARCHAR(MAX)
	SELECT @current_version = version FROM versionTable

	IF (@newVersion > (SELECT MAX(final_version) FROM procedureTable) OR @newVersion < 1)
		RAISERROR ('Bad version', 10, 1)
	ELSE
	BEGIN
		IF @newVersion = @current_version
			PRINT('You are already on this version!');
		ELSE
		BEGIN
			IF @current_version > @newVersion
			BEGIN
				WHILE @current_version > @newVersion 
					BEGIN
						SELECT @procedureName = procedure_name FROM procedureTable WHERE initial_version = @current_version AND final_version = @current_version-1
						PRINT('Executing ' + @procedureName);
						EXEC (@procedureName)
						SET @current_version = @current_version - 1
					END
			END

			IF @current_version < @newVersion
			BEGIN
				WHILE @current_version < @newVersion 
					BEGIN
						SELECT @procedureName = procedure_name FROM procedureTable WHERE initial_version = @current_version AND final_version = @current_version+1
						PRINT('Executing ' + @procedureName);
						EXEC (@procedureName)
						SET @current_version = @current_version + 1
					END
			END

			UPDATE versionTable SET version = @newVersion
		END
	END

EXEC goToVersion 1

SELECT *
FROM versionTable

SELECT *
FROM procedureTable
