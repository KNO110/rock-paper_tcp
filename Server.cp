using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class Server
{
    public static void Main()
    {
        TcpListener server = null;
        try
        {
            int port = 20042;
            IPAddress localAddr = IPAddress.Parse("127.0.0.1");

            server = new TcpListener(localAddr, port);

            server.Start();

            Byte[] bytes = new Byte[256];
            String data = null;

            Console.WriteLine("Waiting for a connection...");

            TcpClient client = server.AcceptTcpClient();
            Console.WriteLine("Connected!");

            data = null;

            NetworkStream stream = client.GetStream();

            int i;

            for (i = 0; i < 5; i++)
            {
                data = null;
                while (true)
                {
                    bytes = new byte[256];
                    int bytesRec = stream.Read(bytes, 0, bytes.Length);
                    data = Encoding.ASCII.GetString(bytes, 0, bytesRec);
                    if (!string.IsNullOrEmpty(data))
                    {
                        Console.WriteLine("Received: {0}", data);
                        break;
                    }
                }

                string response = GetResult(data);  /// получеаем Результат
                byte[] msg = Encoding.ASCII.GetBytes(response);

                stream.Write(msg, 0, msg.Length);
            }

            client.Close();
        }
        catch (SocketException e)
        {
            Console.WriteLine("SocketException: {0}", e);
        }
        finally
        {
            server.Stop();
        }

        Console.WriteLine("\nPress enter to continue...");
        Console.Read();
    }

    static string GetResult(string clientChoice)
    {
        string[] choices = { "Rock", "Scissors", "Paper" };
        Random random = new Random();
        string serverChoice = choices[random.Next(0, 3)];

        if (clientChoice == serverChoice)
            return "Draw";
        else if ((clientChoice == "Rock" && serverChoice == "Scissors") ||
                 (clientChoice == "Scissors" && serverChoice == "Paper") ||
                 (clientChoice == "Paper" && serverChoice == "Rock"))
            return "Ti pobedil";
        else
            return "Server pobedil";
    }
}
