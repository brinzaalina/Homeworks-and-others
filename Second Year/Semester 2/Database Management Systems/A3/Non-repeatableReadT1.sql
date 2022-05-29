INSERT INTO Fan(fan_id, fan_name, fan_age, fan_country)
VALUES (4, 'Shirlee Morton', 42, 'Australia')
BEGIN TRAN
WAITFOR DELAY '00:00:05'
UPDATE Fan SET fan_country='Romania'
WHERE fan_id = 4
COMMIT TRAN

INSERT INTO Fan(fan_id, fan_name, fan_age, fan_country)
VALUES (5, 'Vincent Joosten', 36, 'Germany')
BEGIN TRAN
WAITFOR DELAY '00:00:05'
UPDATE Fan SET fan_country='Romania'
WHERE fan_id = 5
COMMIT TRAN