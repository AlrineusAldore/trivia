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
    /// Interaction logic for signup.xaml
    /// </summary>
    public partial class signup : Page
    {
        public signup()
        {
            InitializeComponent();
        }


        private void signupB_Click(object sender, RoutedEventArgs e)
        {
            signupM ToMsg = new signupM(this.name.Text, this.password.Text, this.email.Text);
            if (client.SendResvMsg(ToMsg.GetJson(), Global.SIGNUP_CODE) != Global.FAIL_STATUS_STR)
            {
                this.NavigationService.Navigate(new menu());
            }
            else
            {
                MessageBox.Show("Try Asain");
            }
        }

        private void login_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.Navigate(new login());
        }
    }
}
