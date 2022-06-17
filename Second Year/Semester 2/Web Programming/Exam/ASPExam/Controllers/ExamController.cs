using ASPExam.Database;
using ASPExam.Models;
using Microsoft.AspNetCore.Mvc;

namespace ASPExam.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class ExamController : Controller
    {
        private readonly ILogger<ExamController> _logger;

        public ExamController(ILogger<ExamController> logger)
        {
            _logger = logger;
        }

        [HttpPost("auth")]
        public Player? Authenticate([FromBody] Player user)
        {
            DAL dal = new DAL();
            Player? player = dal.authenticate(user.Name);
            return player;
        }

        [HttpGet("playersWithName")]
        public List<Player> GetPlayersWithNameContaining(string name)
        {
            DAL dal = new DAL();
            return dal.GetPlayersWithNameContaining(name);
        }

        [HttpGet("players1")]
        public List<Player> GetPlayersFirstDegree(string name)
        {
            DAL dal = new DAL();
            return dal.getFirstDegree(name);
        }

        [HttpGet("players2")]
        public List<Player> GetPlayersSecondDegree(string name)
        {
            DAL dal = new DAL();
            return dal.getSecondDegree(name);
        }

        [HttpGet("players3")]
        public List<Player> GetPlayersThirdDegree(string name)
        {
            DAL dal = new DAL();
            return dal.getThirdDegree(name);
        }
    }
}