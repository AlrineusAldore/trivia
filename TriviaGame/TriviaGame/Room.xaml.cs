using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TriviaGame
{
    /// <summary>
    /// Interaction logic for Room.xaml
    /// </summary>
    public partial class Room : Page
    {
        public Room()
        {
            InitializeComponent();
            roomStateM roomState = JsonC.SetClassRoomState(client.SendResvMsg("{}", Global.GET_ROOM_STATE_CODE));
            string printPlayers = "";
            string printSettings = "";

            printSettings += "Number of players: " + roomState.players.Length;
            printSettings += "\tNumber of questions: " + roomState.questionCount;
            printSettings += "\tTime per question: " + roomState.answerTimeout;
            this.settings.Text = printSettings;

            for (int i = 0; i < roomState.players.Length; i++)
            {
                printPlayers += "\n" + roomState.players[i];
            }
            this.Players.Text = printPlayers;

            if (MainFrame.IsAdmin) this.exit.Content = "close room";
        }

        private void refres_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Refresh();
        }

        private void exit_Click(object sender, RoutedEventArgs e)
        {
            if (MainFrame.IsAdmin) client.SendResvMsg("{}", Global.CLOSE_ROOM_CODE);
            else client.SendResvMsg("{}", Global.LEAVE_ROOM_CODE);

            this.NavigationService.GoBack();
        }
    }
}
