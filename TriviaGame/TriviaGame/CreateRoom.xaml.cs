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
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Page
    {
        public CreateRoom()
        {
            InitializeComponent();
        }

        private void send_Click(object sender, RoutedEventArgs e)
        {
            CroomsM ToMsg = new CroomsM(this.RoomName.Text, int.Parse(this.NumOfQustions.Text), int.Parse(this.NumOfPlayers.Text), int.Parse(this.TimeForQustion.Text));

            client.SendResvMsg(ToMsg.GetJson(), Global.CREATE_ROOM_CODE);

            MainFrame.IsAdmin = true;
            MainFrame.GetMainFrame().thisFrame.NavigationService.Navigate(new Room());
        }
    }
}
