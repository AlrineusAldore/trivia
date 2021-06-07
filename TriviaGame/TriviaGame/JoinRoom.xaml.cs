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
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Page
    {
        public JoinRoom()
        {
            InitializeComponent();
            roomsM RM = JsonC.SetClassRooms( client.SendResvMsg("{}", "8"));
            string printM = "";

            for (int i = 0; i < RM.Rooms.Length; i++)
            {
                printM += "\n" +  RM.Rooms[i];
            }
            this.rooms.Text = printM;
        }

        private void join_Click(object sender, RoutedEventArgs e)
        {
            MainFrame.RoomId = this.room.Text;
            MainFrame.GetMainFrame().thisFrame.NavigationService.Navigate(new Room());
        }

        private void refres_Click(object sender, RoutedEventArgs e)
        {
            roomsM RM = JsonC.SetClassRooms(client.SendResvMsg("{}", "8"));
            string printM = "";

            for (int i = 0; i < RM.Rooms.Length; i++)
            {
                printM += "\n" + RM.Rooms[i];
            }
            this.rooms.Text = printM;
        }
    }
}
