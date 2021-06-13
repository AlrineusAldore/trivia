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
}
