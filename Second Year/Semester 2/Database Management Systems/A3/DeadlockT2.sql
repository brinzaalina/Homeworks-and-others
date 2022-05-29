--table A: Song, table B: Fan
--SET DEADLOCK_PRIORITY HIGH --solution
BEGIN TRAN
UPDATE Fan SET fan_age=52 WHERE fan_id = 3
WAITFOR DELAY '00:00:10'
UPDATE Song SET song_genre='rock 2' WHERE song_id=2
COMMIT TRAN

--pop, 15