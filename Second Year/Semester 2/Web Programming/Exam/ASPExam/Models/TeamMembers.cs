namespace ASPExam.Models
{
    public class TeamMembers
    {
        private int _id;
        private int _idPlayer1;
        private int _idPlayer2;
        private int _idTeam;
        public TeamMembers(int id, int idPlayer1, int idPlayer2, int idTeam)
        {
            this._id = id;
            this._idPlayer1 = idPlayer1;
            this._idPlayer2 = idPlayer2;
            this._idTeam = idTeam;

        }

        public int Id
        {
            get => _id;
            set => _id = value;
        }

        public int IdPlayer1
        {
            get => _idPlayer1;
            set => _idPlayer1 = value;
        }

        public int IdPlayer2
        {
            get => _idPlayer2;
            set => _idPlayer2 = value;
        }

        public int IdTeam
        {
            get => _idTeam;
            set => _idTeam = value;
        }

    }
}
