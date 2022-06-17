namespace ASPExam.Models
{
    public class Team
    {
        private int _id;
        private string _name;
        private string _homeCity;
        public Team(int id, string name, string homeCity)
        {
            this._id = id;
            this._name = name;
            this._homeCity = homeCity;
        }

        public int Id
        {
            get => _id;
            set => _id = value;
        }

        public string Name
        {
            get => _name;
            set => _name = value;
        }

        public string HomeCity
        {
            get => _homeCity;
            set => _homeCity = value;
        }
    }
}
