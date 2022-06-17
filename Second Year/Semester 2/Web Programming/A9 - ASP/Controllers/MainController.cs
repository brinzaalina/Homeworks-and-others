using A9.Data;
using A9.Models;
using Microsoft.AspNetCore.Mvc;
using System.Linq;
using Microsoft.AspNetCore.Http;

namespace A9.Controllers
{
    public class MainController: Controller
    {
        private DataAbstractLayer _dataAbstractLayer = new DataAbstractLayer();

        public ActionResult Index()
        {
            return View("LoginView");
        }

        [HttpGet("Main/Login")]
        public IActionResult Login(string username, string password)
        {
            List<User> users = _dataAbstractLayer.GetAllUsers();
            User? toReturn = null;
            foreach (User user in users)
                if (user.Username == username && user.Password == password)
                    toReturn = user;
            if (toReturn == null)
            {
                return Unauthorized();
            }
            Token? returnedToken = _dataAbstractLayer.getTokenByUsername(toReturn.Username);
            Token token = new Token();
            if (returnedToken == null)
            {
                token.token = Guid.NewGuid().ToString();
                token.timeout = DateTime.Now.AddDays(1);
                token.username = toReturn.Username;
                _dataAbstractLayer.AddToken(token);
            }
            else
            {
                token.token = Guid.NewGuid().ToString();
                token.timeout = DateTime.Now.AddDays(1);
                token.id = returnedToken.id;
                _dataAbstractLayer.UpdateToken(token);
            }
            return Ok(token);
        }

        public ActionResult Logs()
        {
            var user = HttpContext.Session.GetString("user");
            if (user == null)
            {
                return Redirect("/Main/Login");
            }
            return View("Logs");
        }

        [HttpGet("Main/GetAllLogs")]
        public List<LogReport> GetAllLogs(string token)
        {
            if (token == null)
            {
                return new List<LogReport>();
            }
            if (_dataAbstractLayer.GetToken(token) == null)
            {
                return new List<LogReport>();
            }
            List<LogReport> logReports = _dataAbstractLayer.GetAllLogs();
            return logReports;
        }

        [HttpGet("Main/GetLogsByUser")]
        public List<LogReport> GetLogsByUser(string token)
        {
            if (token == null)
            {
                return new List<LogReport>();
            }
            if (_dataAbstractLayer.GetToken(token) == null)
            {
                return new List<LogReport>();
            }
            List<LogReport> logReports = _dataAbstractLayer.GetLogsByUser(_dataAbstractLayer.GetToken(token).username);
            return logReports;
        }

        [HttpGet("Main/GetLogsByType")]
        public List<LogReport> GetLogsByType(string type)
        {
            List<LogReport> logReports = _dataAbstractLayer.GetLogsByType(type);
            return logReports;
        }

        [HttpGet("Main/GetLogsBySeverity")]
        public List<LogReport> GetLogsBySeverity(string severity)
        {
            List<LogReport> logReports = _dataAbstractLayer.GetLogsBySeverity(severity);
            return logReports;
        }

        [HttpPost("Main/AddLog")]
        public ActionResult AddLog(string token, [FromBody] LogReportDto logReport)
        {
            if (token == null)
            {
                return BadRequest();
            }
            if (_dataAbstractLayer.GetToken(token) == null)
            {
                return BadRequest();
            }
            var user = _dataAbstractLayer.GetToken(token).username;
            _dataAbstractLayer.AddLog(logReport.Type, logReport.Severity, logReport.Date, user,logReport.Logtext);
            return Ok();
        }

        [HttpDelete("Main/RemoveLog")]
        public ActionResult RemoveLog(string token, int id)
        {
            if (token == null)
            {
                return BadRequest();
            }
            if (_dataAbstractLayer.GetToken(token) == null)
            {
                return BadRequest();
            }
            var user = _dataAbstractLayer.GetToken(token).username;
            var logUser = _dataAbstractLayer.GetUserForLogId(id);
            if (user != logUser)
            {
                return BadRequest("You cannot delete this log!");
            }
            _dataAbstractLayer.RemoveLog(id, user);
            return Ok("RemoveLog: success");
        }

        [HttpGet("Main/GetLogsPaginated")]
        public List<LogReport> GetLogsPaginated(string token, int pageNumber, int pageSize)
        {
            if (token == null)
            {
                return new List<LogReport>();
            }
            if (_dataAbstractLayer.GetToken(token) == null)
            {
                return new List<LogReport>();
            }
            List<LogReport> allLogs = _dataAbstractLayer.GetAllLogs();
            var offset = (pageNumber - 1) * pageSize;
            var result = allLogs.Skip(offset).Take(pageSize).ToList();
            return result;
        }

        [HttpGet("Main/GetLogsPaginatedForUser")]
        public List<LogReport> GetLogsPaginatedForUser(string token, int pageNumber, int pageSize)
        {
            if (token == null)
            {
                return new List<LogReport>();
            }
            if (_dataAbstractLayer.GetToken(token) == null)
            {
                return new List<LogReport>();
            }
            List<LogReport> userLogs = _dataAbstractLayer.GetLogsByUser(_dataAbstractLayer.GetToken(token).username);
            var offset = (pageNumber - 1) * pageSize;
            var result = userLogs.Skip(offset).Take(pageSize).ToList();
            return result;
        }

        [HttpGet("Main/GetFilteredLogs")]
        public List<LogReport> GetFilteredLogs(string token, string severity, string type)
        {
            var logs = new List<LogReport>();
            if (token == null)
            {
                return new List<LogReport>();
            }
            if (_dataAbstractLayer.GetToken(token) == null)
            {
                return new List<LogReport>();
            }
            if (severity != null && type != null)
            {
                logs =  _dataAbstractLayer.GetLogsBySeverityAndType(severity, type);

            } else if (type != null)
            {
                logs = this.GetLogsByType(type);
            } else if (severity != null)
            {
                logs = this.GetLogsBySeverity(severity);
            }
            return logs;
        }

        public void Logout()
        {
            HttpContext.Session.Clear();
        }
    }
}
