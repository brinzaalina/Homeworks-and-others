using A9.Models;
using MySql.Data.MySqlClient;

namespace A9.Data
{
    public class DataAbstractLayer
    {
        private static string host = "localhost";
        private static string username = "root";
        private static string password = "";
        private static string database = "logreports";
        private string connectionString = $"server={host};uid={username};pwd={password};database={database}";

        public DataAbstractLayer()
        {
        }

 
        public List<LogReport> GetAllLogs()
        {
            var conn = new MySqlConnection();
            conn.ConnectionString = this.connectionString;
            conn.Open();
            var sql = "SELECT * FROM logs";
            List<LogReport> logReports = new List<LogReport>();
            var command = new MySqlCommand(sql, conn);
            MySqlDataReader mySqlDataReader = command.ExecuteReader();
            while (mySqlDataReader.Read())
            {
                logReports.Add(new LogReport(
                    mySqlDataReader.GetInt32(0),
                    mySqlDataReader.GetString(1),
                    mySqlDataReader.GetString(2),
                    mySqlDataReader.GetDateTime(3),
                    mySqlDataReader.GetString(4),
                    mySqlDataReader.GetString(5)
                    ));
            }
            return logReports;
        }

        public List<User> GetAllUsers()
        {
            var conn = new MySqlConnection();
            conn.ConnectionString = this.connectionString;
            conn.Open();
            var sql = "SELECT * FROM users";
            List<User> users = new List<User>();
            var command = new MySqlCommand(sql, conn);
            MySqlDataReader mySqlDataReader = command.ExecuteReader();
            while (mySqlDataReader.Read())
            {
                users.Add(new User(mySqlDataReader.GetString(0), mySqlDataReader.GetString(1)));
            }
            return users;
        }

        public List<LogReport> GetLogsByUser(string user)
        {
            var conn = new MySqlConnection();
            conn.ConnectionString = this.connectionString;
            conn.Open();
            var sql = "SELECT * FROM logs L WHERE L.user = @user";
            List<LogReport> logs = new List<LogReport>();
            var command = new MySqlCommand(sql, conn);
            command.Parameters.AddWithValue("user", user);
            MySqlDataReader mySqlDataReader = command.ExecuteReader();
            while(mySqlDataReader.Read())
            {
                logs.Add(new LogReport(
                    mySqlDataReader.GetInt32(0),
                    mySqlDataReader.GetString(1),
                    mySqlDataReader.GetString(2),
                    mySqlDataReader.GetDateTime(3),
                    mySqlDataReader.GetString(4),
                    mySqlDataReader.GetString(5)
                    ));
            }
            return logs;
        }

        public List<LogReport> GetLogsBySeverity(string severity)
        {
            var conn = new MySqlConnection();
            conn.ConnectionString = this.connectionString;
            conn.Open();
            var sql = "SELECT * FROM logs L WHERE L.severity = @severity";
            List<LogReport> logs = new List<LogReport>();
            var command = new MySqlCommand(sql, conn);
            command.Parameters.AddWithValue("severity", severity);
            MySqlDataReader mySqlDataReader = command.ExecuteReader();
            while (mySqlDataReader.Read())
            {
                logs.Add(new LogReport(
                    mySqlDataReader.GetInt32(0),
                    mySqlDataReader.GetString(1),
                    mySqlDataReader.GetString(2),
                    mySqlDataReader.GetDateTime(3),
                    mySqlDataReader.GetString(4),
                    mySqlDataReader.GetString(5)
                    ));
            }
            return logs;
        }

        public List<LogReport> GetLogsByType(string type)
        {
            var conn = new MySqlConnection();
            conn.ConnectionString = this.connectionString;
            conn.Open();
            var sql = "SELECT * FROM logs L WHERE L.type = @type";
            List<LogReport> logs = new List<LogReport>();
            var command = new MySqlCommand(sql, conn);
            command.Parameters.AddWithValue("type", type);
            MySqlDataReader mySqlDataReader = command.ExecuteReader();
            while (mySqlDataReader.Read())
            {
                logs.Add(new LogReport(
                    mySqlDataReader.GetInt32(0),
                    mySqlDataReader.GetString(1),
                    mySqlDataReader.GetString(2),
                    mySqlDataReader.GetDateTime(3),
                    mySqlDataReader.GetString(4),
                    mySqlDataReader.GetString(5)
                    ));
            }
            return logs;
        }

        public List<LogReport> GetLogsBySeverityAndType(string severity, string type)
        {
            var conn = new MySqlConnection();
            conn.ConnectionString = this.connectionString;
            conn.Open();
            var sql = "SELECT * FROM logs L WHERE L.type = @type AND L.severity = @severity";
            List<LogReport> logs = new List<LogReport>();
            var command = new MySqlCommand(sql, conn);
            command.Parameters.AddWithValue("severity", severity);
            command.Parameters.AddWithValue("type", type);
            MySqlDataReader mySqlDataReader = command.ExecuteReader();
            while (mySqlDataReader.Read())
            {
                logs.Add(new LogReport(
                    mySqlDataReader.GetInt32(0),
                    mySqlDataReader.GetString(1),
                    mySqlDataReader.GetString(2),
                    mySqlDataReader.GetDateTime(3),
                    mySqlDataReader.GetString(4),
                    mySqlDataReader.GetString(5)
                    ));
            }
            return logs;
        }

        public int AddLog(string type, string severity, DateTime date, string user, string logtext)
        {
            var conn = new MySqlConnection();
            conn.ConnectionString = this.connectionString;
            conn.Open();
            var sql = "INSERT INTO logs(type, severity, date, user, logtext) VALUES (@type, @severity, @date, @user, @logtext)";
            var command = new MySqlCommand(sql, conn);
            command.Parameters.AddWithValue("type", type);
            command.Parameters.AddWithValue("severity", severity);
            command.Parameters.AddWithValue("date", date);
            command.Parameters.AddWithValue("user", user);
            command.Parameters.AddWithValue("logtext", logtext);
            command.Prepare();
            return command.ExecuteNonQuery();
        }

        public int RemoveLog(int id, string user)
        {
            var conn = new MySqlConnection();
            conn.ConnectionString = this.connectionString;
            conn.Open();
            var sql = "DELETE FROM logs WHERE id = @id AND user = @user";
            var command = new MySqlCommand(sql, conn);
            command.Parameters.AddWithValue("id", id);
            command.Parameters.AddWithValue("user", user);
            return command.ExecuteNonQuery();
        }

        public string GetUserForLogId(int id)
        {
            var conn = new MySqlConnection();
            conn.ConnectionString = this.connectionString;
            conn.Open();
            var sql = "SELECT * FROM logs WHERE id = @id";
            var command = new MySqlCommand(sql, conn);
            command.Parameters.AddWithValue("id", id);
            MySqlDataReader mySqlDataReader = command.ExecuteReader();
            var user = "";
            while (mySqlDataReader.Read())
            {
                user = mySqlDataReader.GetString(4);
            }
            return user;
        }

        public Token AddToken(Token token)
        {
            try
            {
                var conn = new MySqlConnection();
                conn.ConnectionString = this.connectionString;
                conn.Open();
                var sql = "INSERT INTO tokens(username, token, timeout) VALUES (@username, @token, @timeout)";
                MySqlCommand cmd = new MySqlCommand(sql, conn);
                cmd.Parameters.AddWithValue("username", token.username);
                cmd.Parameters.AddWithValue("token", token.token);
                cmd.Parameters.AddWithValue("timeout", token.timeout);
                cmd.ExecuteNonQuery();
            }
            catch (MySqlException ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.Message);
            }
            return token;
        }

        public Token UpdateToken(Token token)
        {
            string a = "update tokens set token='" + token.token + "', " +
                       "timeout = " + "STR_TO_DATE( '" + token.timeout + "','%m/%d/%Y %H:%i:%s')" +
                       " where id = " + token.id;
            try
            {
                var conn = new MySqlConnection();
                conn.ConnectionString = this.connectionString;
                conn.Open();
                var sql = "UPDATE tokens SET token = @token, timeout = @timeout WHERE id = @id";
                MySqlCommand cmd = new MySqlCommand(sql, conn);
                cmd.Parameters.AddWithValue("token", token.token);
                cmd.Parameters.AddWithValue("timeout", token.timeout);
                cmd.Parameters.AddWithValue("id", token.id);
                cmd.ExecuteNonQuery();
            }
            catch (MySqlException ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.Message);
            }

            return token;
        }
        public Token? GetToken(string token)
        {
            Token tokenToBeReturned = null;
            try
            {
                var conn = new MySqlConnection();
                conn.ConnectionString = this.connectionString;
                conn.Open();
                var sql = "SELECT * FROM tokens WHERE token = @token";
                MySqlCommand cmd = new MySqlCommand(sql, conn);
                cmd.Parameters.AddWithValue("token", token);
                MySqlDataReader myreader = cmd.ExecuteReader();

                while (myreader.Read())
                {
                    tokenToBeReturned = new Token();
                    tokenToBeReturned.id = myreader.GetInt32("id");
                    tokenToBeReturned.username = myreader.GetString("username");
                    tokenToBeReturned.token = myreader.GetString("token");
                    tokenToBeReturned.timeout = myreader.GetDateTime("timeout");
                }
                myreader.Close();
                if (tokenToBeReturned.timeout > DateTime.Now)
                {
                    return tokenToBeReturned;
                }
                else
                {
                    return null;
                }
            }
            catch (MySqlException ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.Message);
            }
            return null;
        }

        public Token? getTokenByUsername(string username)
        {
            Token? tokenToBeReturned = null;
            try
            {
                var conn = new MySqlConnection();
                conn.ConnectionString = this.connectionString;
                conn.Open();
                var sql = "SELECT * FROM tokens WHERE username = @username";
                MySqlCommand cmd = new MySqlCommand(sql, conn);
                cmd.Parameters.AddWithValue("username", username);
                MySqlDataReader myreader = cmd.ExecuteReader();

                while (myreader.Read())
                {
                    tokenToBeReturned = new Token();
                    tokenToBeReturned.id = myreader.GetInt32("id");
                    tokenToBeReturned.username = myreader.GetString("username");
                    tokenToBeReturned.token = myreader.GetString("token");
                    tokenToBeReturned.timeout = myreader.GetDateTime("timeout");
                }
                myreader.Close();
            }
            catch (MySqlException ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.Message);
            }

            return tokenToBeReturned;
        }
    }
}
