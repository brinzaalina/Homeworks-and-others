USE Music_Production_Company;
--INSERT STATEMENTS

--MANAGER
INSERT INTO Manager (
	manager_id,
	manager_name,
	manager_phone_number,
	manager_email,
	education,
	manager_salary
) VALUES
	(1, 'Keira Peacock', '0744596670', 'keira.peacock99@gmail.com', 'Florida Atlantic University', 7500),
	(2, 'Amabel Thompkins', '0722554866', 'amabel.thompkins10@yahoo.com', 'DePaul University', 7000),
	(3, 'Annika Otis', '0766156842', 'anni_ot_manager@gmail.com', 'Berklee College of Music', 8000),
	(4, 'Amilia Bain', '0721750760', 'bain.ami@yahoo.com', 'DePaul University', 7250),
	(5, 'Tad Austin', '0769254860', 'austin_drew_tad@gmail.com', 'Florida Atlantic University', 8000),
	(6, 'Deborah Fire', '0736429821', 'debofireman@gmail.com', 'Florida Atlantic University', 6500)
;

--FAN
INSERT INTO Fan (
	fan_id,
	fan_name,
	fan_age,
	fan_country
) VALUES 
	(1, 'Jamie Mercer', 20, 'UK'),
	(2, 'Davis Elliot', 18, 'US'),
	(3, 'Clyde Auteberry', 15, 'Australia'),
	(4, 'Shirlee Morton', 42, 'Australia'),
	(5, 'Vincent Joosten', 36, 'Germany'),
	(6, 'Andrew Josh', 25, 'US'),
	(7, 'Nelly Anderson', 27, 'US')
;

--SINGER
INSERT INTO Singer (
	singer_id,
	singer_name,
	singer_phone_number,
	singer_email,
	manager_id,
	prefered_genre,
	type_of_voice,
	singer_salary
) VALUES
	(1, 'Jessie J', '0775556616', 'jessiejofficial@gmail.com', 1, 'pop', 'soprano', 9000),
	(2, 'Maneskin', '0711555464', 'maneskinofficial@gmail.com', 5, 'rock', 'tenor', 24000),
	(3, 'Maddie & Tae', '0765557786', 'maddieandtaeusofficial@gmail.com', 3, 'country', 'soprano', 15000),
	(4, 'Fergie', '0733463958', 'fergieofficial@gmail.com', 2, 'pop', 'alto', 10000),
	(5, 'Labrinth', '0714563662', 'labrinthofficial@gmail.com', 3, 'pop', 'tenor', 9500),
	(6, 'Maddie Marlow', '0745693862', 'maddiemarlow@gmail.com',2, 'country', 'soprano', 5650)
;

--INSERT INTO Singer
--(singer_id,singer_name,singer_phone_number,singer_email,manager_id,prefered_genre,type_of_voice,singer_salary) 
--VALUES (200, 'The Unknowns', '0725024975', 'theunknownsinger@gmail.com', 1000, 'rock', 'bass', 5000); -- no matching manager for manager_id

--FAN OF SINGER
INSERT INTO Fan_of_singer (
	fan_id, 
	singer_id,
	favourite_song,
	fan_percentage
) VALUES
	(4, 1, 'Domino', 60),
	(1, 5, 'No Ordinary', 78),
	(3, 4, 'Fergalicious', NULL),
	(5, 2, 'ZITTI E BUONI', 92),
	(2, 2, 'MAMMA MIA', 89),
	(1, 2, 'Torna a casa', 81)
;

--SONGS
INSERT INTO Song (
	song_id, 
	song_name,
	song_genre,
	release_date,
	duration,
	likes,
	dislikes
) VALUES
	(1, 'Domino', 'pop', '2011-12-26', 235, 1487130, 540004),
	(2, 'Do It Like A Dude', 'pop', '2010-11-09', 200, 759278, 45230),
	(3, 'MAMMA MIA', 'rock', '2021-10-11', 184, 411521,9559),
	(4, 'ZITTI E BUONI', 'rock', '2021-04-03', 198, 1587834, 40365),
	(5, 'Torna a casa', 'rock', '2018-10-01', 229, 1143363, 39006),
	(6, 'Fly', 'country', '2015-02-23', 222, 236320, 8226),
	(7, 'Fergalicious', 'pop', '2009-06-17', 228, 1361082, 54119),
	(8, 'Clumsy', 'pop', '2009-06-17', 243, 418318,  12288),
	(9, 'No Ordinary', 'pop', '2020-10-09', 186, 94342, 509),
	(10, 'All For Us', 'pop', '2019-08-05', 193, 272783, 4696)
;

--SINGS_IN 
INSERT INTO Sings_in (
	singer_id,
	song_id
) VALUES 
	(1, 1),
	(4, 1),
	(1, 2),
	(2, 3),
	(2, 4),
	(2, 5),
	(3, 6),
	(4, 7),
	(4, 8),
	(5, 9),
	(5, 10),
	(2, 10)
;

--REVIEW
INSERT INTO Review (
	review_id,
	review_text,
	no_of_likes,
	no_of_dislikes,
	no_of_replies,
	song_id
) VALUES 
	(1, 'Meravigliosa canzone così come l’estetica del video!', 4456, 128, 60, 5),
	(2, 'This song  is a masterpiece!', 172, 6, 2, 5),
	(3, 'This sound is amazing, ROCK AND ROLLS NEVER DIES', 79, 0, 0, 4),
	(4, 'What an amazing harmonious feeling. Im goosbumping right now.', 1486, 23, 1, 10),
	(5, 'Still one of her best song !', 1, 0, 0, 2)
;

--PRODUCER
INSERT INTO Producer (
	producer_id,
	producer_name,
	producer_phone_number,
	producer_email,
	experience,
	license_code,
	producer_salary
) VALUES
	(1, 'Henry Russell Walter', '0751545166', 'walterproduction@gmail.com', 13, 'HRW23041986', 15000),
	(2, 'Fabrizio Ferraguzzo', '0783276598', 'fabiferraprod@gmail.com', 5, 'FF15051990', 12540),
	(3, 'William James Adams Jr.', '0726159607', 'will.i.amofficialproduction@gmail.com', 26, 'WJA15031975', 19350),
	(4, 'Parker Ibrahim Ighile', '0764258315', 'parkeriiprod@gmail.com', 9, 'PII01031990', 11000),
	(5, 'Dann Huff', '0715698542', 'dannhuffproducerofficial@gmail.com', 40, 'DH15111960', 20000),
	(6, 'Amelia Dalindo', '0762861495', 'amedalproduction@gmail.com', 2, 'AD10051995', 10000)
;

--PRODUCES
INSERT INTO Produces (
	producer_id,
	song_id
) VALUES 
	(1, 1),
	(4, 1),
	(5, 2),
	(2, 3),
	(2, 4),
	(2, 5),
	(3, 5),
	(4, 5),
	(3, 7),
	(3, 8),
	(5, 6),
	(1, 9),
	(4, 10)
;

--COMPOSER
INSERT INTO Composer (
	composer_id,
	composer_name,
	composer_phone_number,
	composer_email,
	prefered_instrument,
	manager_id
) VALUES 
	(1, 'Tiffany Vartanyan', '0765289654', 'tiffvart@gmail.com', 'guitar', 3),
	(2, 'Kim Nazel', '0716985465', 'kimnizel@gmail.com', 'piano', 5),
	(3, 'Jake Sinclair', '0735984257', 'jakesin@gmail.com', 'violin', 4),
	(4, 'Jimmy Forrest', '0716952046', 'jimmyforrest@gmail.com', 'drums', 2)
;

--COMPOSES
INSERT INTO Composes (
	composer_id,
	song_id
) VALUES
	(1, 6),
	(2, 6),
	(3, 6),
	(1, 9),
	(1, 10),
	(2, 1),
	(2, 2),
	(2, 7),
	(1, 8),
	(2, 8),
	(3, 3),
	(3, 4),
	(3, 5)
;

--LYRIST
INSERT INTO Lyrist (
	lyrist_id,
	lyrist_name,
	lyrist_phone_number,
	lyrist_email,
	lyrist_salary,
	prefered_lyrics_genre
) VALUES
	(1, 'Maddie Marlow', '0745693862', 'maddiemarlow@gmail.com', 9000, 'country'),
	(2, 'Jimmy Forrest', '0769215684', 'jimmyforrest@gmail.com', 10000, 'pop'),
	(3, 'Taylor Parks', '0756924165', 'taylorparks@gmail.com', 6750, 'rock'),
	(4, 'Jake Sinclair', '0726301982', 'jakesin@gmail.com', 5000, 'rock')
;

--WRITES
INSERT INTO Writes (
	lyrist_id,
	song_id
) VALUES
	(1, 6),
	(2, 6),
	(1, 9),
	(2, 10),
	(2, 7),
	(2, 8),
	(3, 1),
	(3, 3),
	(1, 4),
	(2, 4),
	(3, 4),
	(3, 5),
	(2, 2)
;

INSERT INTO Playlist (
	playlist_id,
	playlist_name
) VALUES  
	(1, 'Rock Hits'),
	(2, 'Pop Hits'),
	(3, 'Country Hits')
;

INSERT INTO Song_in_playlist (
	playlist_id,
	song_id
) VALUES 
	(1, 3),
	(1, 4),
	(1, 5),
	(2, 10),
	(2, 9)
;

--UPDATE STATEMENTS

SELECT *
FROM Manager; -- original table

--update the salary of the manager with the manager_id=5 to 8500
UPDATE Manager SET manager_salary=8500 WHERE manager_id=5 -- used =

SELECT *
FROM Manager; -- modified table

--update the age of the fans from UK, Germany and US that are older than 19 and younger than 30

SELECT *
FROM Fan; -- original table

UPDATE Fan SET fan_age=fan_age+1 WHERE fan_country IN ('UK', 'Germany', 'US') AND fan_age BETWEEN 19 AND 30 -- used AND, IN, BETWEEN

SELECT *
FROM Fan; -- modified table

--update the fan percentage that a fan has for a singer to no longer be null

SELECT *
FROM Fan_of_singer; -- original table

UPDATE Fan_of_singer SET fan_percentage=50 WHERE fan_percentage IS NULL -- used IS NULL

SELECT *
FROM Fan_of_singer; -- modified table

--DELETE STATEMENTS
INSERT INTO Review (
	review_id,
	review_text,
	no_of_likes,
	no_of_dislikes,
	no_of_replies,
	song_id
) VALUES
	(6, 'It is crap, hate it.', 1854, 900, 100, 2)
;

INSERT INTO Fan (
	fan_id,
	fan_name,
	fan_age,
	fan_country
) VALUES
	(100, 'Johnny Cashmier', 120, 'China')
;
--delete the reviews that contain the word "crap" in them
DELETE
FROM Review 
WHERE review_text LIKE '%crap%' -- used LIKE
--delete the fans that are older than 100 years
DELETE 
FROM Fan 
WHERE fan_age > 100 -- used >

--QUERIES
--a) two queries with the union operation; use UNION [ALL] and OR
--The manager Annika Otis holds a meeting and at the meeting the only persons that can attend are the singers and composers managed by her
SELECT S.singer_name 
FROM Singer S
WHERE S.manager_id = 3
UNION
SELECT C.composer_name 
FROM Composer C 
WHERE C.manager_id = 3

--Select all the managers whose managed singers are tenors or whose managed composers prefer piano, eliminating duplicates
--used DISTINCT
SELECT DISTINCT  M.manager_name
FROM Manager M, Singer S, Composer C
WHERE (M.manager_id = S.manager_id AND S.type_of_voice = 'tenor') OR (M.manager_id = C.manager_id AND C.prefered_instrument = 'piano')

--b) two queries with the intersection operation; use INTERSECT and IN
--All composers who are also lyrists
SELECT C.composer_name 
FROM Composer C
INTERSECT
SELECT L.lyrist_name 
FROM Lyrist L

--All composers who are also lyrists (alternative with IN)
SELECT C.composer_name 
FROM Composer C 
WHERE C.composer_name IN (SELECT L.lyrist_name FROM Lyrist L)

--c) two queries with the difference operation; use EXCEPT and NOT IN
--Songs that are pop or rock, but are not the favorite song of a fan
--condition in the WHERE clause with OR
SELECT S.song_name 
FROM Song S
WHERE S.song_genre = 'pop' OR S.song_genre = 'rock'
EXCEPT
SELECT FS.favourite_song 
FROM Fan_of_singer FS

--Songs that are pop or rock, but are not the favourite song of a fan (alternative with NOT IN)
--condition in the WHERE clause with (), OR, AND
SELECT S.song_name 
FROM Song S
WHERE (S.song_genre = 'pop' OR S.song_genre = 'rock') AND S.song_name NOT IN (SELECT FS.favourite_song FROM Fan_of_singer FS)

--d) 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN and FULL JOIN (one query per operator); one query will join at least 3 tables, while another one will join at least two m:n relationships
--INNER JOIN
--Get for each song the reviews that it has
SELECT S.song_name, R.review_text
FROM Song S INNER JOIN Review R on R.song_id = S.[song_id]

--LEFT JOIN
--Print all the managers and their managed singers and composers, including the ones that have no managed singers or composers
--join 3 tables: Manager, Singer, Composer
SELECT M.manager_name, S.singer_name, C.composer_name
FROM Manager M 
LEFT JOIN Singer S ON M.manager_id = S.manager_id
LEFT JOIN Composer C ON M.manager_id = C.manager_id

--RIGHT JOIN
--Print all the songs including the lyrists that worked on them; include lyrist that did not work on any song
SELECT S.song_name, L.lyrist_name
FROM Song S
RIGHT JOIN Writes W ON W.song_id = S.song_id
RIGHT JOIN Lyrist L ON L.lyrist_id = W.lyrist_id

--FULL JOIN
--Print all the producers with songs that are in at least one playlist; include songs that are not in a playlist, producers that don't have songs and playlists that are empty
--join at least two many-to-many relationships
SELECT Pr.producer_name, SG.song_name, P.playlist_name
FROM Producer Pr
FULL JOIN Produces Prs ON Prs.producer_id = Pr.producer_id
FULL JOIN Song SG ON SG.song_id = Prs.song_id
FULL JOIN Song_in_playlist SP ON SP.song_id = SG.song_id 
FULL JOIN Playlist P ON P.playlist_id = SP.playlist_id


--e) 2 queries with the IN operator and a subquery in the WHERE clause; in at least one case, the subquery should include a subquery in its own WHERE clause
--Print the name of singers which have songs that are in playlists
--used DISTINCT
SELECT S.singer_name
FROM Singer S
WHERE S.singer_id IN (
	SELECT DISTINCT SNG.singer_id
	FROM Song S2 
	INNER JOIN Sings_in SG ON S2.song_id = SG.song_id
	INNER JOIN Singer SNG ON SG.singer_id = SNG.singer_id
	WHERE SG.song_id IN (
		SELECT S3.song_id
		FROM Song S3
		INNER JOIN Song_in_playlist SP ON SP.song_id = S3.song_id
		INNER JOIN Playlist P ON P.playlist_id = SP.playlist_id
	)
)

--Print the name of singers which have fans that have as a favourite song a song longer than 200 seconds with reviews.
--condition in the WHERE clause with AND, NOT
--used DISTINCT
SELECT S.singer_name 
FROM Singer S
WHERE S.singer_id IN (
	SELECT FS.singer_id
	FROM Fan_of_singer FS
	WHERE FS.favourite_song IN (
		SELECT SG.song_name 
		FROM Song SG
		WHERE NOT SG.duration < 200 AND SG.song_id IN (
			SELECT DISTINCT R.song_id
			FROM Review R
		)
	)
)

--f) 2 queries with the EXISTS operator and a subquery in the WHERE clause
--Print singers that have fans
--Multiply their salary by 1.5 because they have fans and this means that their music is good (arithmetic operation in the SELECT clause)
SELECT S.singer_name, S.singer_salary * 1.5 AS NewSalary
FROM Singer S
WHERE EXISTS(
	SELECT *
	FROM Singer S2 
	INNER jOIN Fan_of_singer FS ON S2.singer_id = FS.singer_id
	INNER JOIN Fan F ON F.fan_id = FS.fan_id
	WHERE S2.singer_id = S.singer_id
)

--Print playlists that are not empty
SELECT P.playlist_name 
FROM Playlist P 
WHERE EXISTS(
	SELECT * 
	FROM Song S
	INNER JOIN Song_in_playlist SP ON S.song_id = SP.song_id
	INNER JOIN Playlist P2 ON P2.playlist_id = SP.playlist_id
	WHERE P2.playlist_id = P.playlist_id
)

--g) 2 queries with a subquery in the FROM clause
--Print the managers which have a salary of at least 7500 and are managers for singers
--Their salary will increase with 100 as a bonus for their hard work (arithmetic operation in the SELECT clause)
--condition in the WHERE clause with NOT
--used DISTINCT
SELECT m.manager_name, m.manager_salary + 100 AS increased_salary
FROM (
	SELECT *
	FROM Manager M
	WHERE NOT M.manager_salary < 7500
)m WHERE m.manager_id IN (
	SELECT DISTINCT S.manager_id
	FROM Singer S
)
ORDER BY increased_salary DESC

--Print the songs that have reviews with at least 1000 likes which are in playlists
--The number of likes will increase with 50 and the number of dislikes will decrease with 50, since the song has good reviews 
--arithmetic operation in the SELECT clause
--order ascending by the number of likes
SELECT s.song_name, s.likes + 50 AS likes, s.dislikes - 50 AS dislikes, s.no_of_likes AS likes_for_review, s.review_text
FROM (
	SELECT S.song_name, S.likes, S.dislikes, R.song_id, R.no_of_likes, R.review_text
	FROM Song S INNER JOIN Review R on S.song_id = R.song_id
	WHERE R.no_of_likes >= 1000
)s WHERE s.song_id IN (
	SELECT S2.song_id
	FROM Song S2
	INNER JOIN Song_in_playlist SP ON S2.song_id = SP.song_id
	INNER JOIN Playlist P ON P.playlist_id = SP.playlist_id
)
ORDER BY likes ASC

--h) 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 2 of the latter will also have a subquery in the HAVING clause; use the aggregation operators: COUNT, SUM, AVG, MIN, MAX
--Print countries and the number of fans for each of them
--used COUNT
SELECT F.fan_country, COUNT(*) AS fans
FROM Fan F
GROUP BY F.fan_country

--Print the singers with the most fans
--contains the HAVING clause
--has a subquery in the HAVING clause
--used COUNT, MAX
SELECT S.singer_id, S.singer_name, COUNT(*) AS fans
FROM Singer S INNER JOIN Fan_of_singer FS ON S.singer_id = FS.singer_id INNER JOIN Fan F ON F.fan_id = FS.fan_id
GROUP BY S.singer_id, S.singer_name
HAVING COUNT(*) = (
	SELECT MAX(T.C)
	FROM (
		SELECT COUNT(*) C
		FROM Singer S2 INNER JOIN Fan_of_singer FS2 ON S2.singer_id = FS2.singer_id INNER JOIN Fan F2 ON F2.fan_id = FS2.fan_id
		GROUP BY S2.singer_id, S2.singer_name
	)T
)

SELECT S.singer_id, S.singer_name, COUNT(*) AS fans
FROM Singer S INNER JOIN Fan_of_singer FS ON S.singer_id = FS.singer_id
GROUP BY S.singer_id, S.singer_name


--Print the minimum from all the total durations per genre
--contains the HAVING clause
--has a subquery in the HAVING clause
--used SUM, MIN
SELECT S.song_genre, SUM(S.duration) AS total_duration
FROM Song S
GROUP BY S.song_genre
HAVING SUM(S.duration) = (
	SELECT MIN(T.s)
	FROM (
		SELECT SUM(S2.duration) s
		FROM Song S2
		GROUP BY S2.song_genre
	)T
)

--Print the average number of dislikes for each song genre with at least 2 songs released after 2016
--used AVG, COUNT
--contains the HAVING clause
--has a subquery in the HAVING clause
SELECT S.song_genre, AVG(S.dislikes) AS average_dislikes
FROM Song S
GROUP BY S.song_genre
HAVING 1 < (SELECT COUNT(S2.song_genre)
			FROM Song S2
			WHERE S.song_genre = S2.song_genre AND S2.release_date >= '2017-01-01')

--i) 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2/operator); rewrite 2 of them with aggregation operators, and the other 2 with IN/[NOT] IN
--Find the top 5 songs which have more likes than the least appreciated pop song
--using ANY
--using ORDER BY likes

SELECT TOP 5 S.*
FROM Song S
WHERE S.likes > ANY (
	SELECT S2.likes
	FROM Song S2
	WHERE S2.song_genre = 'pop')
ORDER BY S.likes DESC

--rewritten with an aggregation operator
--use MIN instead of ANY
SELECT TOP 5 S.*
FROM Song S
WHERE S.likes > (
	SELECT MIN(S2.likes)
	FROM Song S2
	WHERE S2.song_genre = 'pop')
ORDER BY S.likes DESC


--find all the reviews for the newest songs (songs that were released in 2020 or 2021)
--using ANY
SELECT R.*
FROM Review R
WHERE R.song_id = ANY(
	SELECT S.song_id
	FROM Song S
	WHERE S.release_date >= '2020-01-01')

--rewritten with IN
SELECT R.*
FROM Review R
WHERE R.song_id IN (
	SELECT S.song_id
	FROM Song S
	WHERE S.release_date >= '2020-01-01')

--Find the top 50% producers for which half of the experience is more than the experience the producers with a salary smaller than 15000
--using ALL
--ordered descending by experience
SELECT TOP 50 PERCENT P.*
FROM Producer P
WHERE P.experience/2 > ALL (
	SELECT P2.experience
	FROM Producer P2
	WHERE P2.producer_salary < 15000)
ORDER BY P.experience DESC

--rewritten with an aggreation operator 
--used MAX instead of ALL
SELECT TOP 50 PERCENT P.*
FROM Producer P
WHERE P.experience > (
	SELECT MAX(P2.experience)
	FROM Producer P2
	WHERE P2.producer_salary < 15000)
ORDER BY P.experience DESC

--Find all the singers that are not lyrists who prefer country lyrics
--using ALL
SELECT S.*
FROM Singer S
WHERE S.singer_name <> ALL (
	SELECT L.lyrist_name
	FROM Lyrist L
	WHERE L.prefered_lyrics_genre LIKE '%country%')

--rewritten using NOT IN
SELECT S.*
FROM Singer S
WHERE S.singer_name NOT IN (
	select L.lyrist_name
	FROM Lyrist L
	WHERE L.prefered_lyrics_genre LIKE '%country%')