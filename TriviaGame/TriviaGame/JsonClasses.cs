using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TriviaGame
{
    class loginM
    {
        public string username { get; set; }
        public string password { get; set; }

        public loginM(string username, string password)
        {
            this.password = password;
            this.username = username;
        }

        public string GetJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented);
        }
    }

    class signupM
    {
        public string username { get; set; }
        public string password { get; set; }
        public string email { get; set; }

        public signupM(string username, string password, string email)
        {
            this.password = password;
            this.username = username;
            this.email = email;
        }

        public string GetJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented);
        }
    }



    class statsM
    {
        public string username { get; set; }
        public string gamesPlayed { get; set; }
        public string totalAnswer { get; set; }
        public string rightAnswers { get; set; }
        public string averageAnswerTime { get; set; }
        public string bestScore { get; set; }

        public statsM(string GamesPlayed, string TotalAnswer, string RightAnswers, string averageAnswerTime, string username, string BestScores)
        {
            this.gamesPlayed = GamesPlayed;
            this.totalAnswer = TotalAnswer;
            this.rightAnswers = RightAnswers;
            this.averageAnswerTime = averageAnswerTime;
            this.username = username;
            this.bestScore = BestScores;
        }

        public string GetJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented);
        }
    }

    class roomsM
    {
        public string[] rooms { get; set; }

        public roomsM(string[] rooms)
        {
            this.rooms = rooms;
        }
    }

    class CroomsM
    {
        public string roomName { get; set; }
        public int questionsCount { get; set; }
        public int maxUsers { get; set; }
        public int answerTimeout { get; set; }


        public CroomsM(string roomName, int questionsCount, int maxUsers, int answerTimeout)
        {
            this.roomName = roomName;
            this.questionsCount = questionsCount;
            this.maxUsers = maxUsers;
            this.answerTimeout = answerTimeout;
        }

        public string GetJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented);
        }
    }

    class playersInRoomM
    {
        public int roomId { get; set; }

        public playersInRoomM(int roomId)
        {
            this.roomId = roomId;
        }

        public string GetJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented);
        }
    }

    static class JsonC
    {
        public static loginM SetClassLogin(string jsonM)
        {
            return JsonConvert.DeserializeObject<loginM>(jsonM);
        }
        public static signupM SetClassSignup(string jsonM)
        {
            return JsonConvert.DeserializeObject<signupM>(jsonM);
        }
        public static statsM SetClassStats(string jsonM)
        {
            return JsonConvert.DeserializeObject<statsM>(jsonM);
        }
        public static roomsM SetClassRooms(string jsonM)
        {
            return JsonConvert.DeserializeObject<roomsM>(jsonM);
        }
        public static playersInRoomM SetClassPlayersInRoom(string jsonM)
        {
            return JsonConvert.DeserializeObject<playersInRoomM>(jsonM);
        }
    }


}
