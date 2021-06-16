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
        public string GamesPlayed { get; set; }
        public string TotalAnswer { get; set; }
        public string RightAnswers { get; set; }
        public string averageAnswerTime { get; set; }
        public string BestUserScore { get; set; }
        public string BestScores { get; set; }

        public statsM(string GamesPlayed, string TotalAnswer, string RightAnswers, string averageAnswerTime, string BestUserScore, string BestScores)
        {
            this.GamesPlayed = GamesPlayed;
            this.TotalAnswer = TotalAnswer;
            this.RightAnswers = RightAnswers;
            this.averageAnswerTime = averageAnswerTime;
            this.BestUserScore = BestUserScore;
            this.BestScores = BestScores;
        }

        public string GetJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented);
        }
    }

    class roomsM
    {
        public string[] Rooms { get; set; }

        public roomsM(string[] Rooms)
        {
            this.Rooms = Rooms;
        }
    }

    class CroomsM
    {
        public string username { get; set; }
        public string Qustions { get; set; }
        public string NumOfPlayers { get; set; }
        public string time { get; set; }


        public CroomsM(string username, string Qustions, string NumOfPlayers, string time)
        {
            this.username = username;
            this.Qustions = Qustions;
            this.NumOfPlayers = NumOfPlayers;
            this.time = time;
        }

        public string GetJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented);
        }
    }

    class playersInRoomM
    {
        public string playersInRoom { get; set; }

        public playersInRoomM(string playersInRoom)
        {
            this.playersInRoom = playersInRoom;
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
