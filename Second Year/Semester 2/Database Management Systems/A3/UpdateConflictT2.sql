SET TRAN ISOLATION LEVEL SNAPSHOT
BEGIN TRAN
WAITFOR DELAY '00:00:05'
-- T1 has updated and has a lock on the table
-- T2 will be blocked when trying to update the table
UPDATE Fan SET fan_age = 22 WHERE fan_id = 100
COMMIT TRAN