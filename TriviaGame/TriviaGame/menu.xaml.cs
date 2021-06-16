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
    /// Interaction logic for menu.xaml
    /// </summary>
    public partial class menu : Page
    {
        public menu()
        {
            InitializeComponent();
        }

        private void CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            show.NavigationService.Navigate( new CreateRoom());
        }

        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {
            show.NavigationService.Navigate(new JoinRoom());
        }

        private void Statistics_Click(object sender, RoutedEventArgs e)
        {
            this.show.NavigationService.Navigate(new Stats());
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
