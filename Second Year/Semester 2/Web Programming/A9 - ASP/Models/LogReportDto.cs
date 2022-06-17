namespace A9.Models
{
    public class LogReportDto
    {
        private string _type;
        private string _severity;
        private DateTime _date;
        private string _logtext;

        public LogReportDto(string type, string severity, DateTime date, string logtext)
        {
            this._type = type;
            this._severity = severity;
            this._date = date;
            this._logtext = logtext;
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


        public string Logtext
        {
            get => _logtext;
            set => _logtext = value;
        }
    }
}
