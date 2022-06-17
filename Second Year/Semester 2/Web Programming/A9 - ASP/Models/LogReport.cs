namespace A9.Models
{
    public class LogReport
    {
        private int _id;
        private string _type;
        private string _severity;
        private DateTime _date;
        private string _user;
        private string _logtext;

        public LogReport(string type, string severity, DateTime date, string user, string logtext)
        {
            this._type = type;
            this._severity = severity;
            this._date = date;
            this._user = user;
            this._logtext = logtext;
        }

        public LogReport(int id, string type, string severity, DateTime date, string user, string logtext)
        {
            this._id = id;
            this._type = type;
            this._severity = severity;
            this._date = date;
            this._user = user;
            this._logtext = logtext;
        }

        public int Id
        {
            get => _id;
        }

        public string Type
        {
            get => _type;
            set => _type = value;
        }

        public string Severity
        {
            get => _severity;
            set => _severity = value;
        }

        public DateTime Date
        {
            get => _date;
            set => _date = value;
        }

        public string User
        {
            get => _user;
            set => _user = value;
        }

        public string Logtext
        {
            get => _logtext;
            set => _logtext = value;
        }
    }
}
