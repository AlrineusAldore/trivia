using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TriviaGame
{
    class MainFrame
    {
        public static MainWindow MFrame;
        public static string RoomId;

        public MainFrame(MainWindow MW)
        {
            MFrame = MW;
        }

        public static MainWindow GetMainFrame()
        {
            return MFrame;
        }
    }

    public static class Global
    {
        public const string IP = "127.0.0.1";
        public const int PORT = 8820;

        public const int OK_STATUS = 1;
        public const int FAIL_STATUS = 0;

        public const int LOGIN_CODE = 100;
        public const int SIGNUP_CODE = 69;
        public const int ERROR_CODE = 42;
        public const int GET_PLAYERS_IN_ROOM_CODE = 3;
        public const int CREATE_ROOM_CODE = 2;
        public const int JOIN_ROOM_CODE = 12;
        public const int GET_PERSONAL_STATS_CODE = 11;

        public const int GET_HIGH_SCORE_CODE = 10;
        public const int LOGOUT_CODE = 9;
        public const int GET_ROOMS_CODE = 8;
        public const int CLOSE_ROOM_CODE = 7;
        public const int START_GAME_CODE = 6;
        public const int GET_ROOM_STATE_CODE = 5;
        public const int LEAVE_ROOM_CODE = 4;
        
    }
}
