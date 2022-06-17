namespace ASPExam.Models
{
    public class Player
    {
        private int _id;
        private string _name;
        private string _position;
        public Player(int id, string name, string position)
        {
            this._id = id;
            this._name = name;
            this._position = position;
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

        public string Position
        {
            get => _position;
            set => _position = value;
        }
    }
}
