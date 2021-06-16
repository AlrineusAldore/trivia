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

            Console.WriteLine("client msg: " + msg);
            byte[] binBuf = bytesToBinBytes(buf);
            clientStream.Write(binBuf, 0, binBuf.Length);
            clientStream.Flush();
            return true;
        }

        public static string ResvMsg()
        {
            byte[] buffer = new byte[32]; //4 * 8
            clientStream.Read(new byte[8], 0, 8); //get rid of code
            int bytesRead = clientStream.Read(buffer, 0, 32);
            Console.WriteLine("bin len from server: " + Encoding.UTF8.GetString(buffer));
            byte[] lenBytes = Encoding.UTF8.GetBytes(binToStr(Encoding.UTF8.GetString(buffer)));

            if (BitConverter.IsLittleEndian)
            {
                Array.Reverse(lenBytes);
                Console.WriteLine("reversed");
            }
            //int len = BitConverter.ToInt32(lenBytes, 0);
            Console.Write("lenBytes bin: ");
            foreach(byte element in lenBytes)
            {
                Console.Write(element + " ");
            }
            int len = lenBytes[0] | (lenBytes[1] << 8) | (lenBytes[2] << 16) | (lenBytes[3] << 24); ;
            Console.WriteLine("\nserver len: " +len);

            buffer = new byte[len * 8];
            bytesRead = clientStream.Read(buffer, 0, len * 8);

            Console.WriteLine("bytes read: " + bytesRead);
            return binToStr(Encoding.UTF8.GetString(buffer)).Substring(5);
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

        public static byte[] bytesToBinBytes(byte[] bytes)
        {
            string binStr = "";

            for (int i = 0; i < bytes.Length; i++)
                binStr += Convert.ToString(bytes[i], 2).PadLeft(8, '0');


            return Encoding.ASCII.GetBytes(binStr);
        }

        public static string binToStr(string data)
        {
            List<Byte> byteList = new List<Byte>();
            Console.WriteLine("binStr len: " + data.Length);
            if (!isBin(data))
            {
                Console.WriteLine("client::binToStr - error: string isnt binary");
                return "error";
            }
            for (int i = 0; i < data.Length; i += 8)
            {
                byteList.Add(Convert.ToByte(data.Substring(i, 8), 2));
            }
            return Encoding.ASCII.GetString(byteList.ToArray());
        }

        public static bool isBin(string s)
        {
            foreach (var c in s)
                if (c != '0' && c != '1')
                    return false;
            return true;
        }
    }
}
