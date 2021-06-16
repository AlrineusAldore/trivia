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
    /// Interaction logic for Stats.xaml
    /// </summary>
    public partial class Stats : Page
    {
        public Stats()
        {
            InitializeComponent();
            statsM SM = JsonC.SetClassStats(client.SendResvMsg("{}", Global.GET_PERSONAL_STATS_CODE));
            string printM = "name - " + SM.username;
                   printM = "\nGames Played - " + SM.gamesPlayed;
                   printM = "\nTotal Answer - " + SM.totalAnswer;
                   printM = "\nRight Answers - " + SM.rightAnswers;
                   printM = "\naverage Answer Time - " + SM.averageAnswerTime;
                   printM = "\nBest Score - " + SM.bestScore;
            this.Players.Text = printM;
        }
    }
}

/*
 *         public string GamesPlayed { get; set; }
        public string TotalAnswer { get; set; }
        public string RightAnswers { get; set; }
        public string averageAnswerTime { get; set; }
        public string BestUserScore { get; set; }
        public string BestScores { get; set; }
 * */
