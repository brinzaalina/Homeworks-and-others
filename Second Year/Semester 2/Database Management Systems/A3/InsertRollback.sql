--Song, Playlist, Song_in_playlist
CREATE OR ALTER PROCEDURE addRowSong @name VARCHAR(50), @genre VARCHAR(25), @releaseDate DATE, @duration INT, @likes INT, @dislikes INT AS
BEGIN
	SET NOCOUNT ON
	DECLARE @maxId INT
	SET @maxId = 1
	SELECT TOP 1 @maxId = song_id + 1 FROM Song ORDER BY song_id DESC
	DECLARE @error VARCHAR(max)
	SET @error = ''
	IF(@name IS NULL)
	BEGIN
		SET @error = 'Song name must be non null'
		RAISERROR('Song name must be non null', 16, 1);
	END
	IF(@genre IS NULL)
	BEGIN
		SET @error = 'Song genre must be non null'
		RAISERROR('Song genre must be non null', 16, 1);
	END
	IF(@releaseDate IS NULL)
	BEGIN
		SET @error = 'Release date must be non null'
		RAISERROR('Release date must be non null', 16, 1);
	END
	IF(@duration < 0)
	BEGIN 
		SET @error = 'Duration must be positive'
		RAISERROR('Duration must be positive', 16, 1);
	END
	IF(@likes < 0)
	BEGIN
		SET @error = 'The number of likes must be positive'
		RAISERROR('The number of likes must be positive', 16, 1);
	END
	IF(@dislikes < 0)
	BEGIN
		SET @error = 'The number of dislikes must be positive'
		RAISERROR('The number of dislikes must be positive', 16, 1);
	END
	INSERT INTO Song(song_id, song_name, song_genre, release_date, duration, likes, dislikes)
	VALUES (@maxId, @name, @genre, @releaseDate, @duration, @likes, @dislikes)
	EXEC sp_log_changes '', @name, 'Add row to song', @error
END


GO
CREATE OR ALTER PROCEDURE addRowPlaylist @name VARCHAR(300) AS
BEGIN
	SET NOCOUNT ON
	DECLARE @maxId INT
	SET @maxId = 1
	SELECT TOP 1 @maxId = playlist_id + 1 FROM Playlist ORDER BY playlist_id DESC
	DECLARE @error VARCHAR(max)
	SET @error = ''
	IF(@name IS NULL)
	BEGIN
		SET @error = 'Playlist name must be non null'
		RAISERROR('Playlist name must be non null', 16, 1);
	END
	INSERT INTO Playlist(playlist_id, playlist_name) 
	VALUES (@maxId, @name)
	EXEC sp_log_changes '', @name, 'Add row to playlist', @error
END

GO
CREATE OR ALTER PROCEDURE addRowSongInPlaylist @songName VARCHAR(50), @playlistName VARCHAR(300) AS
BEGIN
	SET NOCOUNT ON
	DECLARE @error VARCHAR(max)
	SET @error = ''
	IF(@songName IS NULL)
	BEGIN
		SET @error = 'Song name must be non null'
		RAISERROR(@error, 16, 1);
	END
	IF(@playlistName IS NULL)
	BEGIN
		SET @error = 'Playlist name must be non null'
		RAISERROR(@error, 16, 1);
	END
	DECLARE @songId INT
	SET @songId = (SELECT song_id FROM Song WHERE song_name = @songName)
	DECLARE @playlistId INT
	SET @playlistId = (SELECT playlist_id FROM Playlist WHERE playlist_name = @playlistName)
	IF(@songId IS NULL)
	BEGIN
		SET @error = 'No song with the given name'
		RAISERROR(@error, 16, 1);
	END
	IF(@playlistId IS NULL)
	BEGIN
		SET @error = 'No playlist with the given name'
		RAISERROR(@error, 16, 1);
	END
	INSERT INTO Song_in_playlist VALUES (@songId, @playlistId)
	DECLARE @newData VARCHAR(350)
	SET @newData = @songName + ' ' + @playlistName
	EXEC sp_log_changes '', @newData, 'Connect song to playlist', @error
END

EXEC addRowSong 'Domino', 'pop', '2011-12-26', 235, 1487130, 540004
EXEC addRowPlaylist 'Pop hits'
EXEC addRowSongInPlaylist 'Domino', 'Pop hits'

SELECT * FROM Song
SELECT * FROM Playlist
SELECT * FROM Song_in_playlist
SELECT * FROM LogChanges
DELETE FROM Song_in_playlist
DELETE FROM Song
DELETE FROM Playlist
DELETE FROM LogChanges

GO
CREATE OR ALTER PROCEDURE successfulAddRollback AS
BEGIN
	BEGIN TRAN
	BEGIN TRY 
		EXEC addRowSong 'Domino', 'pop', '2011-12-26', 235, 1487130, 540004
		EXEC addRowPlaylist 'Pop hits'
		EXEC addRowSongInPlaylist 'Domino', 'Pop hits'
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		EXEC sp_log_changes '', '', 'rolledback all data', ''
		RETURN
	END CATCH
	COMMIT TRAN
END

GO 
CREATE OR ALTER PROCEDURE failAddRollback AS
BEGIN
	BEGIN TRAN
	BEGIN TRY
		EXEC addRowSong 'Domino', 'pop', '2011-12-26', 235, 1487130, 540004
		EXEC addRowPlaylist 'Pop hits'
		EXEC addRowSongInPlaylist 'Do', 'Pop hits'
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		EXEC sp_log_changes '', '', 'rolledback all data', ''
		RETURN
	END CATCH
	COMMIT TRAN
END

EXEC successfulAddRollback
EXEC failAddRollback