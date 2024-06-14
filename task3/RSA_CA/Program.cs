using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;//import dll

namespace RSA_CS
{
    internal class Program
    {
        [DllImport("RSA_DLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "KeyGen")]
        public static extern void KeyGen (string fotmat, int keySize, string privateKeyFile, string publicKeyFile);
        [DllImport("RSA_DLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Encrypt")]
        public static extern void Encrypt(string format, string publicKeyFile, string plainTextFile, string cipherTextFile);
        [DllImport("RSA_DLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Decrypt")]
        public static extern void Decrypt(string format, string privateKeyFile, string recoverTextFile, string cipherTextFile);


        static void Main(string[] args)
        {

            if (args.Length != 5)
            {
                Console.WriteLine("Usage: RSA_CLI <OPTION>");
                Console.WriteLine("Options:");
                Console.WriteLine("\tkeygen  <keyFormat> <keySize> <privateFile> <publicFile>");
                Console.WriteLine("\tencrypt <keyFormat> <publicFile> <plainTextFile> <cipherTextFile>");
                Console.WriteLine("\tdecrypt <keyFormat> <privateFile> <recoverTextFile> <cipherTextFile>");
                Environment.Exit(-1);
            }

            string mode = args[0];
            if (mode.Equals("keygen"))
            {
                KeyGen(args[1], Int32.Parse(args[2]), args[3], args[4]);
            }
            else if (mode.Equals("encrypt"))
            {
                Encrypt(args[1], args[2], args[3], args[4]);
            }
            else if (mode.Equals("decrypt"))
            {
                Decrypt(args[1], args[2], args[3], args[4]);
            }
            else
            {
                Console.WriteLine("Usage: RSA_CLI <OPTION>");
                Console.WriteLine("Options:");
                Console.WriteLine("\tkeygen <keyFormat> <keySize> <privateFile> <publicFile>");
                Console.WriteLine("\tencrypt <keyFormat> <publicFile> <plainTextFile> <cipherTextFile>");
                Console.WriteLine("\tdecrypt <keyFormat> <privateFile> <recoverTextFile> <cipherTextFile>");
                Environment.Exit(-1);
            }

            Environment.Exit(0);
        }
    }
}