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
        public string gamesPlayed { get; set; }
        public string totalAnswers { get; set; }
        public string rightAnswers { get; set; }
        public string averageAnswerTime { get; set; }
        public string bestScore { get; set; }

        public statsM(string gamesPlayed, string totalAnswers, string rightAnswers, string averageAnswerTime, string bestScore)
        {
            this.gamesPlayed = gamesPlayed;
            this.totalAnswers = totalAnswers;
            this.rightAnswers = rightAnswers;
            this.averageAnswerTime = averageAnswerTime;
            this.bestScore = bestScore;
        }

        public string GetJson()
        {
            return JsonConvert.SerializeObject(this, Formatting.Indented);
        }
    }

    class roomsM
    {
        public roomDataM[] rooms { get; set; }

        public roomsM(roomDataM[] rooms)
        {
            this.rooms = rooms;
        }
    }

    class roomDataM
    {
        public uint roomId { get; set; }
        public string name { get; set; }
        public uint maxPlayers { get; set; }
        public uint numOfQuestionsInGame { get; set; }
        public uint timePerQuestion { get; set; }
        public bool isActive { get; set; }

        public roomDataM(uint roomId, string name, uint maxPlayers, uint numOfQuestionsInGame, uint timePerQuestion, bool isActive)
        {
            this.roomId = roomId;
            this.name = name;
            this.maxPlayers = maxPlayers;
            this.numOfQuestionsInGame = numOfQuestionsInGame;
            this.timePerQuestion = timePerQuestion;
            this.isActive = isActive;

        }
    }

    class roomStateM
    {
        public bool hasGameBegan { get; set; }
        public int questionCount { get; set; }
        public int answerTimeout { get; set; }
        public string[] players { get; set; }

        public roomStateM(bool hasGameBegan, int questionCount, int answerTimeout, string[] players)
        {
            this.hasGameBegan = hasGameBegan;
            this.questionCount = questionCount;
            this.answerTimeout = answerTimeout;
            this.players = players;
        }
    }

    class CroomsM
    {
        public string roomName { get; set; }
        public int questionCount { get; set; }
        public int maxUsers { get; set; }
        public int answerTimeout { get; set; }


        public CroomsM(string roomName, int questionCount, int maxUsers, int answerTimeout)
        {
            this.roomName = roomName;
            this.questionCount = questionCount;
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
        public static roomStateM SetClassRoomState(string jsonM)
        {
            return JsonConvert.DeserializeObject<roomStateM>(jsonM);
        }
    }


}
