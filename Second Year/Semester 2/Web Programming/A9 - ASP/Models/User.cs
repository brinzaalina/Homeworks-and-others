namespace A9.Models
{
    public class User
    {
        private string _username;
        private string _password;

        public User(string username, string password)
        {
            this._username = username;
            this._password = password;
        }

        public string Username
        {
            get => _username;
            set => _username = value;
        }

        public string Password
        {
            get => _password;
            set => _password = value;
        }
    }
}
