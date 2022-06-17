using ASPExam.Models;
using Npgsql;

namespace ASPExam.Database
{
    public class DAL
    {

        private static string host = "localhost";
        private static string username = "postgres";
        private static string password = "test123";
        private static string database = "exam";
        private string connectionString = $"server={host};uid={username};pwd={password};database={database}";

        public DAL()
        {

        }

        public Player? authenticate(string name)
        {
            var conn = new NpgsqlConnection();
            conn.ConnectionString = this.connectionString;
            conn.Open();
            var sql = "SELECT * FROM player WHERE name = @name";
            Player? user = null;
            var command = new NpgsqlCommand(sql, conn);
            command.Parameters.AddWithValue("name", name);
            command.Prepare();
            NpgsqlDataReader npgsqlDataReader = command.ExecuteReader();
            while (npgsqlDataReader.Read())
            {
                user = new Player(
                    npgsqlDataReader.GetInt32(0),
                    npgsqlDataReader.GetString(1),
                    npgsqlDataReader.GetString(2)
                    );

            }
            conn.Close();
            return user;
        }

        public List<Player> GetPlayersWithNameContaining(string name)
        {
            var conn = new NpgsqlConnection();
            conn.ConnectionString = this.connectionString;
            conn.Open();
            var sql = "SELECT * FROM player WHERE name LIKE @match";
            List<Player> players = new List<Player>();
            var command = new NpgsqlCommand(sql, conn);
            var match = "%" + name + "%";
            command.Parameters.AddWithValue("match", match);
            command.Prepare();
            NpgsqlDataReader reader = command.ExecuteReader();
            while (reader.Read())
            {
                players.Add(new Player(
                    reader.GetInt32(0),
                    reader.GetString(1),
                    reader.GetString(2)
                    ));
            }
            conn.Close();
            return players;
        }

        public Player? GetPlayerById(int id)
        {
            var conn = new NpgsqlConnection();
            conn.ConnectionString = this.connectionString;
            conn.Open();
            var sql = "SELECT * FROM player WHERE id = @id";
            Player? user = null;
            var command = new NpgsqlCommand(sql, conn);
            command.Parameters.AddWithValue("id", id);
            command.Prepare();
            NpgsqlDataReader npgsqlDataReader = command.ExecuteReader();
            while (npgsqlDataReader.Read())
            {
                user = new Player(
                    npgsqlDataReader.GetInt32(0),
                    npgsqlDataReader.GetString(1),
                    npgsqlDataReader.GetString(2)
                    );

            }
            conn.Close();
            return user;
        }

        public List<Player> getFirstDegree(string currentPlayer)
        {
            var current = authenticate(currentPlayer);
            var conn = new NpgsqlConnection();
            conn.ConnectionString = this.connectionString;
            conn.Open();
            var sql = "SELECT * FROM teammembers WHERE idplayer1 = @id";
            List<Player> players = new List<Player>();
            var command = new NpgsqlCommand(sql, conn);
            command.Parameters.AddWithValue("id", current.Id);
            command.Prepare();
            NpgsqlDataReader reader = command.ExecuteReader();
            while (reader.Read())
            {
                players.Add(GetPlayerById(reader.GetInt32(2)));
            }
            conn.Close();
            return players;
        }

        public List<Player> getSecondDegree(string currentPlayer)
        {
            var current = authenticate(currentPlayer);
            var conn = new NpgsqlConnection();
            conn.ConnectionString = this.connectionString;
            conn.Open();
            var sql = "SELECT * FROM teammembers WHERE idplayer1 = @id";
            List<Player> players1 = new List<Player>();
            List<Player> players2 = new List<Player>();
            var command = new NpgsqlCommand(sql, conn);
            command.Parameters.AddWithValue("id", current.Id);
            command.Prepare();
            NpgsqlDataReader reader = command.ExecuteReader();
            while (reader.Read())
            {
                players1 = getFirstDegree(GetPlayerById(reader.GetInt32(2)).Name);
                players2.AddRange(players1);
            }
            conn.Close();
            return players2;
        }

        public List<Player> getThirdDegree(string currentPlayer)
        {
            var current = authenticate(currentPlayer);
            var conn = new NpgsqlConnection();
            conn.ConnectionString = this.connectionString;
            conn.Open();
            var sql = "SELECT * FROM teammembers WHERE idplayer1 = @id";
            List<Player> players1 = new List<Player>();
            List<Player> players2 = new List<Player>();
            var command = new NpgsqlCommand(sql, conn);
            command.Parameters.AddWithValue("id", current.Id);
            command.Prepare();
            NpgsqlDataReader reader = command.ExecuteReader();
            while (reader.Read())
            {
                players1 = getSecondDegree(GetPlayerById(reader.GetInt32(2)).Name);
                players2.AddRange(players1);
            }
            conn.Close();
            return players2;
        }
    }
}
