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

            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse(Global.IP), Global.PORT);

            client.Connect(serverEndPoint);

            clientStream = client.GetStream();
        }

        public static bool SendMsg(string msg, int code)
        {
            byte[] buf = new byte[msg.Length+5]; //code(1) + len(4) + msg(len)

            buf[0] = Convert.ToByte(code); //add code to buffer
            Array.Copy(NumTo4Bytes(msg.Length), 0, buf, 1, 4); //add length to buffer
            Array.Copy(Encoding.ASCII.GetBytes(msg), 0, buf, 5, msg.Length); //add msg to buffer

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
        
        public static string SendResvMsg(string msg, int code)
        {
            if (SendMsg(msg, code))
            {
                return ResvMsg();
            }
            return "Error";
        }

        //public json StringToJson()

        public static byte[] NumTo4Bytes(int num)
        {
            byte[] bytes = new byte[4];
            try
            {
                unchecked
                {
                    bytes[0] = (byte)(num >> 24);
                    bytes[1] = (byte)(num >> 16);
                    bytes[2] = (byte)(num >> 8);
                    bytes[3] = (byte)(num);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Error at converting num to byte arr. Exception: " +e.ToString()+ "\n");
            }

            return bytes;
        }
    }
}
