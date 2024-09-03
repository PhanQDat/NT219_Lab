namespace RSA_GUI
{
    partial class RSA
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            tabControl1 = new TabControl();
            tabPage1 = new TabPage();
            label12 = new Label();
            comboBox2 = new ComboBox();
            label11 = new Label();
            label10 = new Label();
            rich_pri = new RichTextBox();
            rich_pub = new RichTextBox();
            checkBox2 = new CheckBox();
            checkBox1 = new CheckBox();
            label3 = new Label();
            label2 = new Label();
            btn_gen = new Button();
            btn_pub = new Button();
            btn_pri = new Button();
            label1 = new Label();
            comboBox1 = new ComboBox();
            tabPage2 = new TabPage();
            label13 = new Label();
            label14 = new Label();
            rich_cipher = new RichTextBox();
            rich_plain = new RichTextBox();
            btn_en = new Button();
            checkBox5 = new CheckBox();
            label6 = new Label();
            btn_cipher = new Button();
            checkBox3 = new CheckBox();
            checkBox4 = new CheckBox();
            label4 = new Label();
            label5 = new Label();
            btn_pub2 = new Button();
            btn_plain = new Button();
            tabPage3 = new TabPage();
            label15 = new Label();
            label16 = new Label();
            rich_recover = new RichTextBox();
            rich_cipher2 = new RichTextBox();
            btn_de = new Button();
            checkBox6 = new CheckBox();
            label7 = new Label();
            btn_cipher2 = new Button();
            checkBox7 = new CheckBox();
            checkBox8 = new CheckBox();
            label8 = new Label();
            label9 = new Label();
            btn_pri2 = new Button();
            btn_recover = new Button();
            tabControl1.SuspendLayout();
            tabPage1.SuspendLayout();
            tabPage2.SuspendLayout();
            tabPage3.SuspendLayout();
            SuspendLayout();
            // 
            // tabControl1
            // 
            tabControl1.Controls.Add(tabPage1);
            tabControl1.Controls.Add(tabPage2);
            tabControl1.Controls.Add(tabPage3);
            tabControl1.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            tabControl1.Location = new Point(2, 1);
            tabControl1.Name = "tabControl1";
            tabControl1.SelectedIndex = 0;
            tabControl1.Size = new Size(1535, 582);
            tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            tabPage1.Controls.Add(label12);
            tabPage1.Controls.Add(comboBox2);
            tabPage1.Controls.Add(label11);
            tabPage1.Controls.Add(label10);
            tabPage1.Controls.Add(rich_pri);
            tabPage1.Controls.Add(rich_pub);
            tabPage1.Controls.Add(checkBox2);
            tabPage1.Controls.Add(checkBox1);
            tabPage1.Controls.Add(label3);
            tabPage1.Controls.Add(label2);
            tabPage1.Controls.Add(btn_gen);
            tabPage1.Controls.Add(btn_pub);
            tabPage1.Controls.Add(btn_pri);
            tabPage1.Controls.Add(label1);
            tabPage1.Controls.Add(comboBox1);
            tabPage1.Location = new Point(4, 41);
            tabPage1.Name = "tabPage1";
            tabPage1.Padding = new Padding(3);
            tabPage1.Size = new Size(1527, 537);
            tabPage1.TabIndex = 0;
            tabPage1.Text = "KeyGen";
            tabPage1.UseVisualStyleBackColor = true;
            // 
            // label12
            // 
            label12.AutoSize = true;
            label12.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label12.Location = new Point(128, 105);
            label12.Name = "label12";
            label12.Size = new Size(140, 32);
            label12.TabIndex = 14;
            label12.Text = "Format Key:";
            // 
            // comboBox2
            // 
            comboBox2.Font = new Font("Segoe UI", 12F);
            comboBox2.FormattingEnabled = true;
            comboBox2.Items.AddRange(new object[] { "DER", "PEM" });
            comboBox2.Location = new Point(283, 102);
            comboBox2.Name = "comboBox2";
            comboBox2.Size = new Size(179, 40);
            comboBox2.TabIndex = 13;
            comboBox2.SelectedIndexChanged += comboBox2_SelectedIndexChanged;
            // 
            // label11
            // 
            label11.AutoSize = true;
            label11.Location = new Point(1216, 21);
            label11.Name = "label11";
            label11.Size = new Size(130, 32);
            label11.TabIndex = 12;
            label11.Text = "Private key";
            // 
            // label10
            // 
            label10.AutoSize = true;
            label10.Location = new Point(683, 21);
            label10.Name = "label10";
            label10.Size = new Size(122, 32);
            label10.TabIndex = 11;
            label10.Text = "Public key";
            // 
            // rich_pri
            // 
            rich_pri.Location = new Point(1032, 56);
            rich_pri.Name = "rich_pri";
            rich_pri.ReadOnly = true;
            rich_pri.Size = new Size(477, 441);
            rich_pri.TabIndex = 10;
            rich_pri.Text = "";
            // 
            // rich_pub
            // 
            rich_pub.Location = new Point(520, 56);
            rich_pub.Name = "rich_pub";
            rich_pub.ReadOnly = true;
            rich_pub.Size = new Size(477, 441);
            rich_pub.TabIndex = 9;
            rich_pub.Text = "";
            // 
            // checkBox2
            // 
            checkBox2.AutoSize = true;
            checkBox2.Enabled = false;
            checkBox2.Location = new Point(468, 231);
            checkBox2.Name = "checkBox2";
            checkBox2.Size = new Size(22, 21);
            checkBox2.TabIndex = 8;
            checkBox2.UseVisualStyleBackColor = true;
            // 
            // checkBox1
            // 
            checkBox1.AutoSize = true;
            checkBox1.Enabled = false;
            checkBox1.Location = new Point(468, 168);
            checkBox1.Name = "checkBox1";
            checkBox1.Size = new Size(22, 21);
            checkBox1.TabIndex = 7;
            checkBox1.UseVisualStyleBackColor = true;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label3.Location = new Point(27, 220);
            label3.Name = "label3";
            label3.Size = new Size(241, 32);
            label3.TabIndex = 6;
            label3.Text = "Chose public key file:";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label2.Location = new Point(27, 161);
            label2.Name = "label2";
            label2.Size = new Size(249, 32);
            label2.TabIndex = 5;
            label2.Text = "Chose private key file:";
            // 
            // btn_gen
            // 
            btn_gen.Font = new Font("Segoe UI", 12F);
            btn_gen.Location = new Point(27, 274);
            btn_gen.Name = "btn_gen";
            btn_gen.Size = new Size(435, 42);
            btn_gen.TabIndex = 4;
            btn_gen.Text = "Generate";
            btn_gen.UseVisualStyleBackColor = true;
            btn_gen.Click += btn_gen_Click;
            // 
            // btn_pub
            // 
            btn_pub.Font = new Font("Segoe UI", 12F);
            btn_pub.Location = new Point(302, 217);
            btn_pub.Name = "btn_pub";
            btn_pub.Size = new Size(160, 42);
            btn_pub.TabIndex = 3;
            btn_pub.Text = "Public Key";
            btn_pub.UseVisualStyleBackColor = true;
            btn_pub.Click += btn_pub_Click;
            // 
            // btn_pri
            // 
            btn_pri.Font = new Font("Segoe UI", 12F);
            btn_pri.Location = new Point(302, 154);
            btn_pri.Name = "btn_pri";
            btn_pri.Size = new Size(160, 42);
            btn_pri.TabIndex = 2;
            btn_pri.Text = "Private Key";
            btn_pri.UseVisualStyleBackColor = true;
            btn_pri.Click += btn_pri_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label1.Location = new Point(27, 59);
            label1.Name = "label1";
            label1.Size = new Size(230, 32);
            label1.TabIndex = 1;
            label1.Text = "Chose key size (bits)";
            // 
            // comboBox1
            // 
            comboBox1.Font = new Font("Segoe UI", 12F);
            comboBox1.FormattingEnabled = true;
            comboBox1.Items.AddRange(new object[] { "1024", "2048", "3072", "4096" });
            comboBox1.Location = new Point(283, 56);
            comboBox1.Name = "comboBox1";
            comboBox1.Size = new Size(179, 40);
            comboBox1.TabIndex = 0;
            comboBox1.SelectedIndexChanged += comboBox1_SelectedIndexChanged;
            // 
            // tabPage2
            // 
            tabPage2.Controls.Add(label13);
            tabPage2.Controls.Add(label14);
            tabPage2.Controls.Add(rich_cipher);
            tabPage2.Controls.Add(rich_plain);
            tabPage2.Controls.Add(btn_en);
            tabPage2.Controls.Add(checkBox5);
            tabPage2.Controls.Add(label6);
            tabPage2.Controls.Add(btn_cipher);
            tabPage2.Controls.Add(checkBox3);
            tabPage2.Controls.Add(checkBox4);
            tabPage2.Controls.Add(label4);
            tabPage2.Controls.Add(label5);
            tabPage2.Controls.Add(btn_pub2);
            tabPage2.Controls.Add(btn_plain);
            tabPage2.Location = new Point(4, 41);
            tabPage2.Name = "tabPage2";
            tabPage2.Padding = new Padding(3);
            tabPage2.Size = new Size(1527, 537);
            tabPage2.TabIndex = 1;
            tabPage2.Text = "Encrypt";
            tabPage2.UseVisualStyleBackColor = true;
            // 
            // label13
            // 
            label13.AutoSize = true;
            label13.Location = new Point(1214, 23);
            label13.Name = "label13";
            label13.Size = new Size(131, 32);
            label13.TabIndex = 23;
            label13.Text = "Cipher text";
            // 
            // label14
            // 
            label14.AutoSize = true;
            label14.Location = new Point(681, 23);
            label14.Name = "label14";
            label14.Size = new Size(112, 32);
            label14.TabIndex = 22;
            label14.Text = "Plain text";
            // 
            // rich_cipher
            // 
            rich_cipher.Location = new Point(1030, 58);
            rich_cipher.Name = "rich_cipher";
            rich_cipher.ReadOnly = true;
            rich_cipher.Size = new Size(477, 441);
            rich_cipher.TabIndex = 21;
            rich_cipher.Text = "";
            // 
            // rich_plain
            // 
            rich_plain.Location = new Point(518, 58);
            rich_plain.Name = "rich_plain";
            rich_plain.ReadOnly = true;
            rich_plain.Size = new Size(477, 441);
            rich_plain.TabIndex = 20;
            rich_plain.Text = "";
            // 
            // btn_en
            // 
            btn_en.Font = new Font("Segoe UI", 12F);
            btn_en.Location = new Point(28, 284);
            btn_en.Name = "btn_en";
            btn_en.Size = new Size(445, 42);
            btn_en.TabIndex = 19;
            btn_en.Text = "Encrypt";
            btn_en.UseVisualStyleBackColor = true;
            btn_en.Click += btn_en_Click;
            // 
            // checkBox5
            // 
            checkBox5.AutoSize = true;
            checkBox5.Enabled = false;
            checkBox5.Location = new Point(479, 235);
            checkBox5.Name = "checkBox5";
            checkBox5.Size = new Size(22, 21);
            checkBox5.TabIndex = 17;
            checkBox5.UseVisualStyleBackColor = true;
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label6.Location = new Point(28, 226);
            label6.Name = "label6";
            label6.Size = new Size(198, 32);
            label6.TabIndex = 16;
            label6.Text = "Chose cipher file:";
            // 
            // btn_cipher
            // 
            btn_cipher.Font = new Font("Segoe UI", 12F);
            btn_cipher.Location = new Point(313, 221);
            btn_cipher.Name = "btn_cipher";
            btn_cipher.Size = new Size(160, 42);
            btn_cipher.TabIndex = 15;
            btn_cipher.Text = "Cipher";
            btn_cipher.UseVisualStyleBackColor = true;
            btn_cipher.Click += btn_cipher_Click;
            // 
            // checkBox3
            // 
            checkBox3.AutoSize = true;
            checkBox3.Enabled = false;
            checkBox3.Location = new Point(479, 111);
            checkBox3.Name = "checkBox3";
            checkBox3.Size = new Size(22, 21);
            checkBox3.TabIndex = 14;
            checkBox3.UseVisualStyleBackColor = true;
            // 
            // checkBox4
            // 
            checkBox4.AutoSize = true;
            checkBox4.Enabled = false;
            checkBox4.Location = new Point(479, 171);
            checkBox4.Name = "checkBox4";
            checkBox4.Size = new Size(22, 21);
            checkBox4.TabIndex = 13;
            checkBox4.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label4.Location = new Point(28, 100);
            label4.Name = "label4";
            label4.Size = new Size(241, 32);
            label4.TabIndex = 12;
            label4.Text = "Chose public key file:";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label5.Location = new Point(28, 162);
            label5.Name = "label5";
            label5.Size = new Size(224, 32);
            label5.TabIndex = 11;
            label5.Text = "Chose plaintext file:";
            // 
            // btn_pub2
            // 
            btn_pub2.Font = new Font("Segoe UI", 12F);
            btn_pub2.Location = new Point(313, 97);
            btn_pub2.Name = "btn_pub2";
            btn_pub2.Size = new Size(160, 42);
            btn_pub2.TabIndex = 10;
            btn_pub2.Text = "Public Key";
            btn_pub2.UseVisualStyleBackColor = true;
            btn_pub2.Click += btn_pub2_Click;
            // 
            // btn_plain
            // 
            btn_plain.Font = new Font("Segoe UI", 12F);
            btn_plain.Location = new Point(313, 157);
            btn_plain.Name = "btn_plain";
            btn_plain.Size = new Size(160, 42);
            btn_plain.TabIndex = 9;
            btn_plain.Text = "PlainText";
            btn_plain.UseVisualStyleBackColor = true;
            btn_plain.Click += btn_plain_Click;
            // 
            // tabPage3
            // 
            tabPage3.Controls.Add(label15);
            tabPage3.Controls.Add(label16);
            tabPage3.Controls.Add(rich_recover);
            tabPage3.Controls.Add(rich_cipher2);
            tabPage3.Controls.Add(btn_de);
            tabPage3.Controls.Add(checkBox6);
            tabPage3.Controls.Add(label7);
            tabPage3.Controls.Add(btn_cipher2);
            tabPage3.Controls.Add(checkBox7);
            tabPage3.Controls.Add(checkBox8);
            tabPage3.Controls.Add(label8);
            tabPage3.Controls.Add(label9);
            tabPage3.Controls.Add(btn_pri2);
            tabPage3.Controls.Add(btn_recover);
            tabPage3.Location = new Point(4, 41);
            tabPage3.Name = "tabPage3";
            tabPage3.Size = new Size(1527, 537);
            tabPage3.TabIndex = 2;
            tabPage3.Text = "Decrypt";
            tabPage3.UseVisualStyleBackColor = true;
            // 
            // label15
            // 
            label15.AutoSize = true;
            label15.Location = new Point(1202, 23);
            label15.Name = "label15";
            label15.Size = new Size(145, 32);
            label15.TabIndex = 33;
            label15.Text = "Recover text";
            // 
            // label16
            // 
            label16.AutoSize = true;
            label16.Location = new Point(681, 23);
            label16.Name = "label16";
            label16.Size = new Size(131, 32);
            label16.TabIndex = 32;
            label16.Text = "Cipher text";
            // 
            // rich_recover
            // 
            rich_recover.Location = new Point(1030, 58);
            rich_recover.Name = "rich_recover";
            rich_recover.ReadOnly = true;
            rich_recover.Size = new Size(477, 441);
            rich_recover.TabIndex = 31;
            rich_recover.Text = "";
            // 
            // rich_cipher2
            // 
            rich_cipher2.Location = new Point(518, 58);
            rich_cipher2.Name = "rich_cipher2";
            rich_cipher2.ReadOnly = true;
            rich_cipher2.Size = new Size(477, 441);
            rich_cipher2.TabIndex = 30;
            rich_cipher2.Text = "";
            // 
            // btn_de
            // 
            btn_de.Font = new Font("Segoe UI", 12F);
            btn_de.Location = new Point(29, 285);
            btn_de.Name = "btn_de";
            btn_de.Size = new Size(445, 42);
            btn_de.TabIndex = 29;
            btn_de.Text = "Decrypt";
            btn_de.UseVisualStyleBackColor = true;
            btn_de.Click += btn_de_Click;
            // 
            // checkBox6
            // 
            checkBox6.AutoSize = true;
            checkBox6.Enabled = false;
            checkBox6.Location = new Point(480, 117);
            checkBox6.Name = "checkBox6";
            checkBox6.Size = new Size(22, 21);
            checkBox6.TabIndex = 28;
            checkBox6.UseVisualStyleBackColor = true;
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label7.Location = new Point(29, 167);
            label7.Name = "label7";
            label7.Size = new Size(198, 32);
            label7.TabIndex = 27;
            label7.Text = "Chose cipher file:";
            // 
            // btn_cipher2
            // 
            btn_cipher2.Font = new Font("Segoe UI", 12F);
            btn_cipher2.Location = new Point(314, 162);
            btn_cipher2.Name = "btn_cipher2";
            btn_cipher2.Size = new Size(160, 42);
            btn_cipher2.TabIndex = 26;
            btn_cipher2.Text = "Cipher";
            btn_cipher2.UseVisualStyleBackColor = true;
            btn_cipher2.Click += btn_cipher2_Click;
            // 
            // checkBox7
            // 
            checkBox7.AutoSize = true;
            checkBox7.Enabled = false;
            checkBox7.Location = new Point(480, 176);
            checkBox7.Name = "checkBox7";
            checkBox7.Size = new Size(22, 21);
            checkBox7.TabIndex = 25;
            checkBox7.UseVisualStyleBackColor = true;
            // 
            // checkBox8
            // 
            checkBox8.AutoSize = true;
            checkBox8.Enabled = false;
            checkBox8.Location = new Point(480, 235);
            checkBox8.Name = "checkBox8";
            checkBox8.Size = new Size(22, 21);
            checkBox8.TabIndex = 24;
            checkBox8.UseVisualStyleBackColor = true;
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label8.Location = new Point(29, 108);
            label8.Name = "label8";
            label8.Size = new Size(249, 32);
            label8.TabIndex = 23;
            label8.Text = "Chose private key file:";
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label9.Location = new Point(29, 226);
            label9.Name = "label9";
            label9.Size = new Size(211, 32);
            label9.TabIndex = 22;
            label9.Text = "Chose recover file:";
            // 
            // btn_pri2
            // 
            btn_pri2.Font = new Font("Segoe UI", 12F);
            btn_pri2.Location = new Point(314, 105);
            btn_pri2.Name = "btn_pri2";
            btn_pri2.Size = new Size(160, 42);
            btn_pri2.TabIndex = 21;
            btn_pri2.Text = "Private Key";
            btn_pri2.UseVisualStyleBackColor = true;
            btn_pri2.Click += btn_pri2_Click;
            // 
            // btn_recover
            // 
            btn_recover.Font = new Font("Segoe UI", 12F);
            btn_recover.Location = new Point(314, 221);
            btn_recover.Name = "btn_recover";
            btn_recover.Size = new Size(160, 42);
            btn_recover.TabIndex = 20;
            btn_recover.Text = "Recovered";
            btn_recover.UseVisualStyleBackColor = true;
            btn_recover.Click += btn_recover_Click;
            // 
            // RSA
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1538, 582);
            Controls.Add(tabControl1);
            Name = "RSA";
            Text = "RSA";
            tabControl1.ResumeLayout(false);
            tabPage1.ResumeLayout(false);
            tabPage1.PerformLayout();
            tabPage2.ResumeLayout(false);
            tabPage2.PerformLayout();
            tabPage3.ResumeLayout(false);
            tabPage3.PerformLayout();
            ResumeLayout(false);
        }

        #endregion

        private TabControl tabControl1;
        private TabPage tabPage1;
        private TabPage tabPage2;
        private TabPage tabPage3;
        private ComboBox comboBox1;
        private Label label1;
        private Button btn_pri;
        private Button btn_pub;
        private Button btn_gen;
        private Label label2;
        private Label label3;
        private CheckBox checkBox1;
        private CheckBox checkBox2;
        private CheckBox checkBox3;
        private CheckBox checkBox4;
        private Label label4;
        private Label label5;
        private Button btn_pub2;
        private Button btn_plain;
        private CheckBox checkBox5;
        private Label label6;
        private Button btn_cipher;
        private Button btn_en;
        private Button btn_de;
        private CheckBox checkBox6;
        private Label label7;
        private Button btn_cipher2;
        private CheckBox checkBox7;
        private CheckBox checkBox8;
        private Label label8;
        private Label label9;
        private Button btn_pri2;
        private Button btn_recover;
        private Label label11;
        private Label label10;
        private RichTextBox rich_pri;
        private RichTextBox rich_pub;
        private Label label12;
        private ComboBox comboBox2;
        private Label label13;
        private Label label14;
        private RichTextBox rich_cipher;
        private RichTextBox rich_plain;
        private Label label15;
        private Label label16;
        private RichTextBox rich_recover;
        private RichTextBox rich_cipher2;
    }
}
