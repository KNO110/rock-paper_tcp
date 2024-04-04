using System;
using System.Net.Sockets;
using System.Text;

class Client
{
    public static void Main()
    {
        try
        {
            int port = 20042;
            TcpClient client = new TcpClient("127.0.0.1", port);
            NetworkStream stream = client.GetStream();

            Console.WriteLine("Connected to server. Begin:)");

            int clientWins = 0;
            int serverWins = 0;
            int draws = 0;

            for (int i = 0; i < 5; i++)
            {
                Console.WriteLine($"Round {i + 1}");
                Console.Write("Enter your choice (Rock, Scissors, Paper): ");
                string choice = Console.ReadLine();

                byte[] data = Encoding.ASCII.GetBytes(choice);
                stream.Write(data, 0, data.Length);

                data = new byte[256];
                string responseData = string.Empty;

                int bytes = stream.Read(data, 0, data.Length);
                responseData = Encoding.ASCII.GetString(data, 0, bytes);
                Console.WriteLine("Result: {0}\n", responseData);

                if (responseData == "Ti pobedil")
                    clientWins++;
                else if (responseData == "Server pobedil")
                    serverWins++;
                else
                    draws++;
            }

            Console.WriteLine("OVER :)");
            Console.WriteLine($"Client Wins: {clientWins}, Server Wins: {serverWins}, Draws: {draws}");

            stream.Close();
            client.Close();
        }
        catch (Exception e)
        {
            Console.WriteLine("Exception: {0}", e);
        }

        Console.WriteLine("\nPress enter to continue...");
        Console.Read();
    }
}
