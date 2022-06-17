namespace A9.Models
{
    public class Token
    {
        public int id { get; set; }
        public string username { get; set; }
        public string token { get; set; }
        public DateTime timeout { get; set; }
    }
}
