using System.Runtime.InteropServices;
using System.Web;

namespace RSA_GUI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        string privatekeyFile;
        string publickeyFile;
        string plaintextFile;
        string cipherFile;
        string recoverFile;
        int keysize = 0;
        string format;
        string format_pri;
        string format_pub;

        [DllImport("RSA_DLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "KeyGen")]
        public static extern void KeyGen(string fotmat, int keySize, string privateKeyFile, string publicKeyFile);
        [DllImport("RSA_DLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Encrypt")]
        public static extern void Encrypt(string format, string publicKeyFile, string plainTextFile, string cipherTextFile);
        [DllImport("RSA_DLL.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, EntryPoint = "Decrypt")]
        public static extern void Decrypt(string format, string privateKeyFile, string recoverTextFile, string cipherTextFile);

        private void btn_pri_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Der files (*.der)|*.der|Pem files (*.pem)|*.pem|All files (*.*)|*.*";
            saveFileDialog.Title = "Select a private key file";
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                privatekeyFile = saveFileDialog.FileName;
                checkBox1.Checked = true;
                format_pri = (privatekeyFile.Split('.').Last()).ToUpper();
            }
            else
                checkBox1.Checked = false;
        }

        private void btn_pub_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Der files (*.der)|*.der|All files (*.*)|*.*";
            saveFileDialog.Title = "Select a public key file";
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                publickeyFile = saveFileDialog.FileName;
                // Process the selected file here
                checkBox2.Checked = true;
                format_pub = (privatekeyFile.Split('.').Last()).ToUpper();
            }
            else
                checkBox2.Checked = false;
        }

        private void btn_gen_Click(object sender, EventArgs e)
        {
            if (keysize == 0)
            {
                MessageBox.Show("Please select the key size");
                return;
            }
            else if (privatekeyFile == null || publickeyFile == null)
            {
                MessageBox.Show("Please select the private and public key files");
                return;
            }
            else if (format_pri != format_pub)
            {
                MessageBox.Show("Error format");
                return;
            }
            else
            {
                format = format_pri;
            }
            KeyGen(format, keysize, privatekeyFile, publickeyFile);
            MessageBox.Show("Success KeyGen", "Success", MessageBoxButtons.OK);
            checkBox1.Checked = false;
            checkBox2.Checked = false;
            privatekeyFile = null;
            publickeyFile = null;
            format = null;
            format_pri = null;
            format_pub = null;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            keysize = Convert.ToInt32(comboBox1.SelectedItem);
        }

        private void btn_pub2_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Der files (*.der)|*.der|Pem files (*.pem)|*.pem|All files (*.*)|*.*";
            openFileDialog.Title = "Select a public key file";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                publickeyFile = openFileDialog.FileName;
                checkBox3.Checked = true;
                format_pub = (publickeyFile.Split('.').Last()).ToUpper();
            }
            else
                checkBox3.Checked = false;
        }

        private void btn_plain_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Txt files (*.txt)|*.txt|All files (*.*)|*.*";
            openFileDialog.Title = "Select a plaintext file";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                plaintextFile = openFileDialog.FileName;
                checkBox4.Checked = true;
            }
            else
                checkBox4.Checked = false;
        }

        private void btn_cipher_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Txt files (*.txt)|*.txt|All files (*.*)|*.*";
            saveFileDialog.Title = "Select a cipher file";
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                cipherFile = saveFileDialog.FileName;
                checkBox5.Checked = true;
            }
            else
                checkBox5.Checked = false;
        }

        private void btn_en_Click(object sender, EventArgs e)
        {
            if (plaintextFile == null || publickeyFile == null || cipherFile == null)
            {
                MessageBox.Show("Please select the plaintext, public key and cipher files");
                return;
            }
            Encrypt(format_pub, publickeyFile, plaintextFile, cipherFile);
            MessageBox.Show("Success Encrypt", "Success", MessageBoxButtons.OK);
            checkBox3.Checked = false;
            checkBox4.Checked = false;
            checkBox5.Checked = false;
            publickeyFile = null;
            plaintextFile = null;
            cipherFile = null;
            format_pub = null;
        }

        private void btn_pri2_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Der files (*.der)|*.der|Pem files (*.pem)|*.pem|All files (*.*)|*.*";
            openFileDialog.Title = "Select a private key file";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                privatekeyFile = openFileDialog.FileName;
                checkBox6.Checked = true;
                format_pri = (privatekeyFile.Split('.').Last()).ToUpper();
            }
            else
                checkBox6.Checked = false;
        }

        private void btn_cipher2_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Txt files (*.txt)|*.txt|All files (*.*)|*.*";
            openFileDialog.Title = "Select a plaintext file";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                cipherFile = openFileDialog.FileName;
                checkBox7.Checked = true;
            }
            else
                checkBox7.Checked = false;
        }

        private void btn_recover_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Txt files (*.txt)|*.txt|All files (*.*)|*.*";
            saveFileDialog.Title = "Select a plaintext file";
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                recoverFile = saveFileDialog.FileName;
                checkBox8.Checked = true;
            }
            else
                checkBox8.Checked = false;
        }

        private void btn_de_Click(object sender, EventArgs e)
        {
            if (privatekeyFile == null || cipherFile == null || recoverFile == null)
            {
                MessageBox.Show("Please select the private key, cipher and recover files");
                return;
            }
            Decrypt(format_pri, privatekeyFile, recoverFile, cipherFile);
            MessageBox.Show("Success Decrypt", "Success", MessageBoxButtons.OK);
            checkBox6.Checked = false;
            checkBox7.Checked = false;
            checkBox8.Checked = false;
            privatekeyFile = null;
            cipherFile = null;
            recoverFile = null;
            format_pri = null;
        }
    }
}
