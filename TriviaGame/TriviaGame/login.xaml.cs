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
    /// Interaction logic for login.xaml
    /// </summary>
    public partial class login : Page
    {
        public login()
        {
            InitializeComponent();
        }
        private void login_Click(object sender, RoutedEventArgs e)
        {
            loginM ToMsg = new loginM(this.name.Text, this.password.Text);

            if (client.SendResvMsg(ToMsg.GetJson(), Global.LOGIN_CODE) != Global.FAIL_STATUS_STR)
            {
                this.NavigationService.Navigate(new menu());
            }
            else 
            {
                MessageBox.Show("Try Asain");
            }

        }

        private void signup_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new signup());
        }
    }
}
