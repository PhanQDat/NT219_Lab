namespace RSA_GUI
{
    partial class Form1
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
            tabControl1.Size = new Size(882, 422);
            tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
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
            tabPage1.Size = new Size(874, 377);
            tabPage1.TabIndex = 0;
            tabPage1.Text = "KeyGen";
            tabPage1.UseVisualStyleBackColor = true;
            // 
            // checkBox2
            // 
            checkBox2.AutoSize = true;
            checkBox2.Enabled = false;
            checkBox2.Location = new Point(649, 191);
            checkBox2.Name = "checkBox2";
            checkBox2.Size = new Size(22, 21);
            checkBox2.TabIndex = 8;
            checkBox2.UseVisualStyleBackColor = true;
            // 
            // checkBox1
            // 
            checkBox1.AutoSize = true;
            checkBox1.Enabled = false;
            checkBox1.Location = new Point(649, 128);
            checkBox1.Name = "checkBox1";
            checkBox1.Size = new Size(22, 21);
            checkBox1.TabIndex = 7;
            checkBox1.UseVisualStyleBackColor = true;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label3.Location = new Point(208, 180);
            label3.Name = "label3";
            label3.Size = new Size(241, 32);
            label3.TabIndex = 6;
            label3.Text = "Chose public key file:";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label2.Location = new Point(208, 121);
            label2.Name = "label2";
            label2.Size = new Size(249, 32);
            label2.TabIndex = 5;
            label2.Text = "Chose private key file:";
            // 
            // btn_gen
            // 
            btn_gen.Font = new Font("Segoe UI", 12F);
            btn_gen.Location = new Point(208, 234);
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
            btn_pub.Location = new Point(483, 177);
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
            btn_pri.Location = new Point(483, 114);
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
            label1.Location = new Point(208, 54);
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
            comboBox1.Location = new Point(464, 51);
            comboBox1.Name = "comboBox1";
            comboBox1.Size = new Size(179, 40);
            comboBox1.TabIndex = 0;
            comboBox1.SelectedIndexChanged += comboBox1_SelectedIndexChanged;
            // 
            // tabPage2
            // 
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
            tabPage2.Size = new Size(874, 377);
            tabPage2.TabIndex = 1;
            tabPage2.Text = "Encrypt";
            tabPage2.UseVisualStyleBackColor = true;
            // 
            // btn_en
            // 
            btn_en.Font = new Font("Segoe UI", 12F);
            btn_en.Location = new Point(202, 231);
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
            checkBox5.Location = new Point(653, 182);
            checkBox5.Name = "checkBox5";
            checkBox5.Size = new Size(22, 21);
            checkBox5.TabIndex = 17;
            checkBox5.UseVisualStyleBackColor = true;
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label6.Location = new Point(202, 173);
            label6.Name = "label6";
            label6.Size = new Size(198, 32);
            label6.TabIndex = 16;
            label6.Text = "Chose cipher file:";
            // 
            // btn_cipher
            // 
            btn_cipher.Font = new Font("Segoe UI", 12F);
            btn_cipher.Location = new Point(487, 168);
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
            checkBox3.Location = new Point(653, 58);
            checkBox3.Name = "checkBox3";
            checkBox3.Size = new Size(22, 21);
            checkBox3.TabIndex = 14;
            checkBox3.UseVisualStyleBackColor = true;
            // 
            // checkBox4
            // 
            checkBox4.AutoSize = true;
            checkBox4.Enabled = false;
            checkBox4.Location = new Point(653, 118);
            checkBox4.Name = "checkBox4";
            checkBox4.Size = new Size(22, 21);
            checkBox4.TabIndex = 13;
            checkBox4.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label4.Location = new Point(202, 47);
            label4.Name = "label4";
            label4.Size = new Size(241, 32);
            label4.TabIndex = 12;
            label4.Text = "Chose public key file:";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label5.Location = new Point(202, 109);
            label5.Name = "label5";
            label5.Size = new Size(224, 32);
            label5.TabIndex = 11;
            label5.Text = "Chose plaintext file:";
            // 
            // btn_pub2
            // 
            btn_pub2.Font = new Font("Segoe UI", 12F);
            btn_pub2.Location = new Point(487, 44);
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
            btn_plain.Location = new Point(487, 104);
            btn_plain.Name = "btn_plain";
            btn_plain.Size = new Size(160, 42);
            btn_plain.TabIndex = 9;
            btn_plain.Text = "PlainText";
            btn_plain.UseVisualStyleBackColor = true;
            btn_plain.Click += btn_plain_Click;
            // 
            // tabPage3
            // 
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
            tabPage3.Size = new Size(874, 377);
            tabPage3.TabIndex = 2;
            tabPage3.Text = "Decrypt";
            tabPage3.UseVisualStyleBackColor = true;
            // 
            // btn_de
            // 
            btn_de.Font = new Font("Segoe UI", 12F);
            btn_de.Location = new Point(209, 231);
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
            checkBox6.Location = new Point(660, 63);
            checkBox6.Name = "checkBox6";
            checkBox6.Size = new Size(22, 21);
            checkBox6.TabIndex = 28;
            checkBox6.UseVisualStyleBackColor = true;
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label7.Location = new Point(209, 113);
            label7.Name = "label7";
            label7.Size = new Size(198, 32);
            label7.TabIndex = 27;
            label7.Text = "Chose cipher file:";
            // 
            // btn_cipher2
            // 
            btn_cipher2.Font = new Font("Segoe UI", 12F);
            btn_cipher2.Location = new Point(494, 108);
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
            checkBox7.Location = new Point(660, 122);
            checkBox7.Name = "checkBox7";
            checkBox7.Size = new Size(22, 21);
            checkBox7.TabIndex = 25;
            checkBox7.UseVisualStyleBackColor = true;
            // 
            // checkBox8
            // 
            checkBox8.AutoSize = true;
            checkBox8.Enabled = false;
            checkBox8.Location = new Point(660, 181);
            checkBox8.Name = "checkBox8";
            checkBox8.Size = new Size(22, 21);
            checkBox8.TabIndex = 24;
            checkBox8.UseVisualStyleBackColor = true;
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label8.Location = new Point(209, 54);
            label8.Name = "label8";
            label8.Size = new Size(249, 32);
            label8.TabIndex = 23;
            label8.Text = "Chose private key file:";
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            label9.Location = new Point(209, 172);
            label9.Name = "label9";
            label9.Size = new Size(211, 32);
            label9.TabIndex = 22;
            label9.Text = "Chose recover file:";
            // 
            // btn_pri2
            // 
            btn_pri2.Font = new Font("Segoe UI", 12F);
            btn_pri2.Location = new Point(494, 51);
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
            btn_recover.Location = new Point(494, 167);
            btn_recover.Name = "btn_recover";
            btn_recover.Size = new Size(160, 42);
            btn_recover.TabIndex = 20;
            btn_recover.Text = "Recovered";
            btn_recover.UseVisualStyleBackColor = true;
            btn_recover.Click += btn_recover_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(885, 420);
            Controls.Add(tabControl1);
            Name = "Form1";
            Text = "Form1";
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
    }
}
