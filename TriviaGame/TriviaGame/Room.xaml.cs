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
            roomsM RM = JsonC.SetClassRooms(client.SendResvMsg("{\"" + MainFrame.RoomId +  "\" : }", Global.GET_PLAYERS_IN_ROOM_CODE));
            string printM = "";

            for (int i = 0; i < RM.rooms.Length; i++)
            {
                printM += "\n" + RM.rooms[i];
            }
            this.Players.Text = printM;
        }

        private void refres_Click(object sender, RoutedEventArgs e)
        {
            roomsM RM = JsonC.SetClassRooms(client.SendResvMsg("{\"" + MainFrame.RoomId + "\" : }", Global.GET_PLAYERS_IN_ROOM_CODE));
            string printM = "";

            for (int i = 0; i < RM.rooms.Length; i++)
            {
                printM += "\n" + RM.rooms[i];
            }
            this.Players.Text = printM;
        }
    }
}
