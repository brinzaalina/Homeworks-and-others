--INSERT INTO Fan(fan_id, fan_name, fan_age, fan_country)
--VALUES 
--	(1, 'Jamie Mercer', 20, 'UK'),
--	(2, 'Davis Elliot', 18, 'US'),
--	(3, 'Clyde Auteberry', 15, 'Australia')
--SELECT * FROM Fan

BEGIN TRANSACTION
UPDATE Fan SET fan_country='Romania'
WHERE fan_id = 2
WAITFOR DELAY '00:00:10'
ROLLBACK TRANSACTION