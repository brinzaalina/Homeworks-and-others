BEGIN TRAN
WAITFOR DELAY '00:00:04'
INSERT INTO Fan(fan_id, fan_name, fan_age, fan_country)
VALUES (6, 'Andrew Josh', 25, 'US')
COMMIT TRAN

BEGIN TRAN
WAITFOR DELAY '00:00:05'
INSERT INTO Fan(fan_id, fan_name, fan_age, fan_country)
VALUES (7, 'Andrew Josh', 25, 'US')
COMMIT TRAN