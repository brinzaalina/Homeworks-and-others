USE Music_Production_Company;

DROP TABLE Sings_in;
DROP TABLE Produces;
DROP TABLE Composes;
DROP TABLE Writes;
DROP TABLE Fan_of_singer;
DROP TABLE Song_in_playlist;
DROP TABLE Review;
DROP TABLE Song;
DROP TABLE Singer;
DROP TABLE Producer;
DROP TABLE Composer;
DROP TABLE Lyrist;
DROP TABLE Manager;
DROP TABLE Fan;
DROP TABLE Playlist;

CREATE TABLE Manager(
	manager_id INT PRIMARY KEY NOT NULL,
	manager_name VARCHAR(50),
	manager_phone_number VARCHAR(10) UNIQUE,
	manager_email VARCHAR(50) UNIQUE,
	education VARCHAR(100),
	manager_salary INT
);
	
CREATE TABLE Song(
	song_id INT PRIMARY KEY NOT NULL,
	song_name VARCHAR(50),
	song_genre VARCHAR(25),
	release_date DATE,
	duration INT,
	likes INT,
	dislikes INT
);

--1(manager):n(singers)
CREATE TABLE Singer(
	singer_id INT PRIMARY KEY NOT NULL,
	manager_id INT FOREIGN KEY REFERENCES Manager(manager_id) ON DELETE CASCADE ON UPDATE CASCADE,
	singer_name VARCHAR(50),
	singer_phone_number VARCHAR(10) UNIQUE,
	singer_email VARCHAR(50) UNIQUE,
	prefered_genre VARCHAR(25),
	type_of_voice VARCHAR(25),
	singer_salary INT
);

--m(singers):n(songs)
CREATE TABLE Sings_in(
	singer_id INT FOREIGN KEY REFERENCES Singer(singer_id) ON DELETE CASCADE ON UPDATE CASCADE,
	song_id INT FOREIGN KEY REFERENCES Song(song_id) ON DELETE CASCADE ON UPDATE CASCADE,
	PRIMARY KEY (singer_id, song_id)
);

CREATE TABLE Producer(
	producer_id INT PRIMARY KEY NOT NULL,
	producer_name VARCHAR(50),
	producer_phone_number VARCHAR(10) UNIQUE,
	producer_email VARCHAR(50) UNIQUE,
	experience INT,
	license_code VARCHAR(25) UNIQUE,
	producer_salary INT
);

--m(producers):n(songs)
CREATE TABLE Produces(
	producer_id INT FOREIGN KEY REFERENCES Producer(producer_id) ON DELETE CASCADE ON UPDATE CASCADE,
	song_id INT FOREIGN KEY REFERENCES Song(song_id) ON DELETE CASCADE ON UPDATE CASCADE,
	PRIMARY KEY (producer_id, song_id)
);

--1(manager):n(Composers)
CREATE TABLE Composer(
	composer_id INT PRIMARY KEY NOT NULL,
	manager_id INT FOREIGN KEY REFERENCES Manager(manager_id) ON DELETE CASCADE ON UPDATE CASCADE,
	composer_name VARCHAR(50),
	composer_phone_number VARCHAR(10) UNIQUE,
	composer_email VARCHAR(50) UNIQUE,
	composer_salary INT,
	prefered_instrument VARCHAR(100)
);

--m(composers):n(songs)
CREATE TABLE Composes(
	composer_id INT FOREIGN KEY REFERENCES Composer(composer_id) ON DELETE CASCADE ON UPDATE CASCADE,
	song_id INT FOREIGN KEY REFERENCES Song(song_id) ON DELETE CASCADE ON UPDATE CASCADE,
	PRIMARY KEY (composer_id, song_id)
);

CREATE TABLE Lyrist(
	lyrist_id INT PRIMARY KEY NOT NULL,
	lyrist_name VARCHAR(50),
	lyrist_phone_number VARCHAR(10) UNIQUE,
	lyrist_email VARCHAR(50) UNIQUE,
	lyrist_salary INT,
	prefered_lyrics_genre VARCHAR(100)
);

--m(lyrists):n(songs)
CREATE TABLE Writes(
	lyrist_id INT FOREIGN KEY REFERENCES Lyrist(lyrist_id) ON DELETE CASCADE ON UPDATE CASCADE,
	song_id INT FOREIGN KEY REFERENCES Song(song_id) ON DELETE CASCADE ON UPDATE CASCADE,
	PRIMARY KEY (lyrist_id, song_id)
);

CREATE TABLE Fan(
	fan_id INT PRIMARY KEY NOT NULL,
	fan_name VARCHAR(50),
	fan_age INT,
	fan_country VARCHAR(50)
);

--m(fans):n(singers)
CREATE TABLE Fan_of_singer(
	fan_id INT FOREIGN KEY REFERENCES Fan(fan_id) ON DELETE CASCADE ON UPDATE CASCADE,
	singer_id INT FOREIGN KEY REFERENCES Singer(singer_id) ON DELETE CASCADE ON UPDATE CASCADE,
	favourite_song VARCHAR(50),
	fan_percentage INT,
	PRIMARY KEY (fan_id, singer_id)
);


--1(song):n(reviews)
CREATE TABLE Review(
	review_id INT PRIMARY KEY NOT NULL,
	song_id INT FOREIGN KEY REFERENCES Song(song_id) ON DELETE CASCADE ON UPDATE CASCADE,
	review_text VARCHAR(300),
	no_of_likes INT,
	no_of_dislikes INT,
	no_of_replies INT
);

CREATE TABLE Playlist (
	playlist_id INT PRIMARY KEY NOT NULL,
	playlist_name VARCHAR(300)
);

--m(song):n(playlist)
CREATE TABLE Song_in_playlist (
	playlist_id INT FOREIGN KEY REFERENCES Playlist(playlist_id) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
	song_id INT FOREIGN KEY REFERENCES Song(song_id) ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
	PRIMARY KEY (playlist_id, song_id)
);
