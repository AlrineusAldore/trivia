using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using Newtonsoft.Json;

namespace TriviaGame
{
    static class client
    {
        static private NetworkStream clientStream;
        public static void SetClient()
        {
            TcpClient client = new TcpClient();

            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 4242);

            client.Connect(serverEndPoint);

            clientStream = client.GetStream();
        }

        public static bool SendMsg(string msg, string code)
        {
            byte[] buf = { };
            Array.Copy(new ASCIIEncoding().GetBytes(code), buf, 1);
            Array.Copy(new ASCIIEncoding().GetBytes("" + msg.Length), buf, 5);
            Array.Copy(new ASCIIEncoding().GetBytes(msg), buf, 5 + msg.Length);

            clientStream.Write(buf, 0, buf.Length);
            clientStream.Flush();
            return true;
        }

        public static string ResvMsg()
        {
            byte[]  buffer = new byte[4096];
            int bytesRead = clientStream.Read(buffer, 0, 4096);

            return System.Text.Encoding.UTF8.GetString(buffer.Skip(5).ToArray());
        }
        
        public static string SendResvMsg(string msg, string code)
        {
            if (SendMsg(msg, code))
            {
                return ResvMsg();
            }
            return "Error";
        }

        //public json StringToJson()
    }
}
