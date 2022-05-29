--EXEC addRowSong 'Domino', 'pop', '2011-12-26', 235, 1487130, 540004
--EXEC addRowSong 'Domino2', 'pop', '2011-12-26', 235, 1487130, 540004
--EXEC addRowSong 'Domino3', 'pop', '2011-12-26', 235, 1487130, 540004

--table A: Song, table B: Fan
BEGIN TRAN
UPDATE Song SET song_genre='rock 1' WHERE song_id=2
WAITFOR DELAY '00:00:10'
UPDATE Fan SET fan_age=51 WHERE fan_id = 3
COMMIT TRAN

--pop, 18
--SELECT * FROM Fan
--SELECT * FROM Song
