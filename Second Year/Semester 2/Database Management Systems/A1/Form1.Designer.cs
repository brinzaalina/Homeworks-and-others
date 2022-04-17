namespace A1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.ManagersView = new System.Windows.Forms.DataGridView();
            this.SingersView = new System.Windows.Forms.DataGridView();
            this.ManagerLabel = new System.Windows.Forms.Label();
            this.SingerLabel = new System.Windows.Forms.Label();
            this.SingerIdLabel = new System.Windows.Forms.Label();
            this.ManagerIdLabel = new System.Windows.Forms.Label();
            this.NameLabel = new System.Windows.Forms.Label();
            this.PhoneLabel = new System.Windows.Forms.Label();
            this.EmailLabel = new System.Windows.Forms.Label();
            this.GenreLabel = new System.Windows.Forms.Label();
            this.VoiceLabel = new System.Windows.Forms.Label();
            this.singerIdText = new System.Windows.Forms.TextBox();
            this.managerIdText = new System.Windows.Forms.TextBox();
            this.nameText = new System.Windows.Forms.TextBox();
            this.phoneText = new System.Windows.Forms.TextBox();
            this.emailText = new System.Windows.Forms.TextBox();
            this.genreText = new System.Windows.Forms.TextBox();
            this.voiceText = new System.Windows.Forms.TextBox();
            this.SalaryLabel = new System.Windows.Forms.Label();
            this.salaryText = new System.Windows.Forms.TextBox();
            this.addButton = new System.Windows.Forms.Button();
            this.removeButton = new System.Windows.Forms.Button();
            this.updateButton = new System.Windows.Forms.Button();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            ((System.ComponentModel.ISupportInitialize)(this.ManagersView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.SingersView)).BeginInit();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // ManagersView
            // 
            this.ManagersView.AllowUserToAddRows = false;
            this.ManagersView.AllowUserToDeleteRows = false;
            this.ManagersView.BackgroundColor = System.Drawing.Color.Snow;
            this.ManagersView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.ManagersView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ManagersView.Location = new System.Drawing.Point(3, 22);
            this.ManagersView.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.ManagersView.Name = "ManagersView";
            this.ManagersView.ReadOnly = true;
            this.ManagersView.RowHeadersWidth = 51;
            this.ManagersView.RowTemplate.Height = 24;
            this.ManagersView.Size = new System.Drawing.Size(642, 441);
            this.ManagersView.TabIndex = 0;
            this.ManagersView.SelectionChanged += new System.EventHandler(this.ManagersView_SelectionChanged);
            // 
            // SingersView
            // 
            this.SingersView.AllowUserToAddRows = false;
            this.SingersView.AllowUserToDeleteRows = false;
            this.SingersView.BackgroundColor = System.Drawing.Color.Snow;
            this.SingersView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.SingersView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SingersView.Location = new System.Drawing.Point(651, 22);
            this.SingersView.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.SingersView.Name = "SingersView";
            this.SingersView.RowHeadersWidth = 51;
            this.SingersView.RowTemplate.Height = 24;
            this.SingersView.Size = new System.Drawing.Size(577, 441);
            this.SingersView.TabIndex = 1;
            this.SingersView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.SingersView_DataError);
            this.SingersView.SelectionChanged += new System.EventHandler(this.SingersView_SelectionChanged);
            // 
            // ManagerLabel
            // 
            this.ManagerLabel.AutoSize = true;
            this.ManagerLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ManagerLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ManagerLabel.Location = new System.Drawing.Point(3, 0);
            this.ManagerLabel.Name = "ManagerLabel";
            this.ManagerLabel.Size = new System.Drawing.Size(642, 20);
            this.ManagerLabel.TabIndex = 2;
            this.ManagerLabel.Text = "Managers";
            // 
            // SingerLabel
            // 
            this.SingerLabel.AutoSize = true;
            this.SingerLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SingerLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SingerLabel.Location = new System.Drawing.Point(651, 0);
            this.SingerLabel.Name = "SingerLabel";
            this.SingerLabel.Size = new System.Drawing.Size(577, 20);
            this.SingerLabel.TabIndex = 3;
            this.SingerLabel.Text = "Singers";
            // 
            // SingerIdLabel
            // 
            this.SingerIdLabel.AutoSize = true;
            this.SingerIdLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SingerIdLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SingerIdLabel.Location = new System.Drawing.Point(3, 0);
            this.SingerIdLabel.Name = "SingerIdLabel";
            this.SingerIdLabel.Size = new System.Drawing.Size(109, 26);
            this.SingerIdLabel.TabIndex = 4;
            this.SingerIdLabel.Text = "Singer ID";
            // 
            // ManagerIdLabel
            // 
            this.ManagerIdLabel.AutoSize = true;
            this.ManagerIdLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ManagerIdLabel.Font = new System.Drawing.Font("Microsoft YaHei", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ManagerIdLabel.Location = new System.Drawing.Point(348, 0);
            this.ManagerIdLabel.Name = "ManagerIdLabel";
            this.ManagerIdLabel.Size = new System.Drawing.Size(120, 26);
            this.ManagerIdLabel.TabIndex = 5;
            this.ManagerIdLabel.Text = "Manager ID";
            // 
            // NameLabel
            // 
            this.NameLabel.AutoSize = true;
            this.NameLabel.Dock = System.Windows.Forms.DockStyle.Left;
            this.NameLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.NameLabel.Location = new System.Drawing.Point(3, 26);
            this.NameLabel.Name = "NameLabel";
            this.NameLabel.Size = new System.Drawing.Size(52, 26);
            this.NameLabel.TabIndex = 6;
            this.NameLabel.Text = "Name";
            // 
            // PhoneLabel
            // 
            this.PhoneLabel.AutoSize = true;
            this.PhoneLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PhoneLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PhoneLabel.Location = new System.Drawing.Point(348, 26);
            this.PhoneLabel.Name = "PhoneLabel";
            this.PhoneLabel.Size = new System.Drawing.Size(120, 26);
            this.PhoneLabel.TabIndex = 7;
            this.PhoneLabel.Text = "Phone Number";
            // 
            // EmailLabel
            // 
            this.EmailLabel.AutoSize = true;
            this.EmailLabel.Dock = System.Windows.Forms.DockStyle.Left;
            this.EmailLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EmailLabel.Location = new System.Drawing.Point(3, 52);
            this.EmailLabel.Name = "EmailLabel";
            this.EmailLabel.Size = new System.Drawing.Size(47, 26);
            this.EmailLabel.TabIndex = 8;
            this.EmailLabel.Text = "Email";
            // 
            // GenreLabel
            // 
            this.GenreLabel.AutoSize = true;
            this.GenreLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GenreLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.GenreLabel.Location = new System.Drawing.Point(348, 52);
            this.GenreLabel.Name = "GenreLabel";
            this.GenreLabel.Size = new System.Drawing.Size(120, 26);
            this.GenreLabel.TabIndex = 9;
            this.GenreLabel.Text = "Prefered Genre";
            // 
            // VoiceLabel
            // 
            this.VoiceLabel.AutoSize = true;
            this.VoiceLabel.Dock = System.Windows.Forms.DockStyle.Left;
            this.VoiceLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.VoiceLabel.Location = new System.Drawing.Point(3, 78);
            this.VoiceLabel.Name = "VoiceLabel";
            this.VoiceLabel.Size = new System.Drawing.Size(109, 100);
            this.VoiceLabel.TabIndex = 10;
            this.VoiceLabel.Text = "Type of Voice";
            // 
            // singerIdText
            // 
            this.singerIdText.Dock = System.Windows.Forms.DockStyle.Left;
            this.singerIdText.Location = new System.Drawing.Point(118, 2);
            this.singerIdText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.singerIdText.Name = "singerIdText";
            this.singerIdText.Size = new System.Drawing.Size(100, 22);
            this.singerIdText.TabIndex = 11;
            // 
            // managerIdText
            // 
            this.managerIdText.Dock = System.Windows.Forms.DockStyle.Left;
            this.managerIdText.Location = new System.Drawing.Point(474, 2);
            this.managerIdText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.managerIdText.Name = "managerIdText";
            this.managerIdText.Size = new System.Drawing.Size(100, 22);
            this.managerIdText.TabIndex = 12;
            // 
            // nameText
            // 
            this.nameText.Dock = System.Windows.Forms.DockStyle.Left;
            this.nameText.Location = new System.Drawing.Point(118, 28);
            this.nameText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.nameText.Name = "nameText";
            this.nameText.Size = new System.Drawing.Size(191, 22);
            this.nameText.TabIndex = 13;
            // 
            // phoneText
            // 
            this.phoneText.Dock = System.Windows.Forms.DockStyle.Left;
            this.phoneText.Location = new System.Drawing.Point(474, 28);
            this.phoneText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.phoneText.Name = "phoneText";
            this.phoneText.Size = new System.Drawing.Size(140, 22);
            this.phoneText.TabIndex = 14;
            // 
            // emailText
            // 
            this.emailText.Dock = System.Windows.Forms.DockStyle.Left;
            this.emailText.Location = new System.Drawing.Point(118, 54);
            this.emailText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.emailText.Name = "emailText";
            this.emailText.Size = new System.Drawing.Size(224, 22);
            this.emailText.TabIndex = 15;
            // 
            // genreText
            // 
            this.genreText.Dock = System.Windows.Forms.DockStyle.Left;
            this.genreText.Location = new System.Drawing.Point(474, 54);
            this.genreText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.genreText.Name = "genreText";
            this.genreText.Size = new System.Drawing.Size(100, 22);
            this.genreText.TabIndex = 16;
            // 
            // voiceText
            // 
            this.voiceText.Dock = System.Windows.Forms.DockStyle.Left;
            this.voiceText.Location = new System.Drawing.Point(118, 80);
            this.voiceText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.voiceText.Name = "voiceText";
            this.voiceText.Size = new System.Drawing.Size(140, 22);
            this.voiceText.TabIndex = 17;
            // 
            // SalaryLabel
            // 
            this.SalaryLabel.AutoSize = true;
            this.SalaryLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SalaryLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SalaryLabel.Location = new System.Drawing.Point(348, 78);
            this.SalaryLabel.Name = "SalaryLabel";
            this.SalaryLabel.Size = new System.Drawing.Size(120, 100);
            this.SalaryLabel.TabIndex = 18;
            this.SalaryLabel.Text = "Salary";
            // 
            // salaryText
            // 
            this.salaryText.Dock = System.Windows.Forms.DockStyle.Left;
            this.salaryText.Location = new System.Drawing.Point(474, 80);
            this.salaryText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.salaryText.Name = "salaryText";
            this.salaryText.Size = new System.Drawing.Size(100, 22);
            this.salaryText.TabIndex = 19;
            // 
            // addButton
            // 
            this.addButton.BackColor = System.Drawing.Color.RosyBrown;
            this.addButton.Dock = System.Windows.Forms.DockStyle.Left;
            this.addButton.FlatAppearance.BorderColor = System.Drawing.Color.RosyBrown;
            this.addButton.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.addButton.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.addButton.Location = new System.Drawing.Point(3, 2);
            this.addButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.addButton.Name = "addButton";
            this.addButton.Size = new System.Drawing.Size(224, 54);
            this.addButton.TabIndex = 20;
            this.addButton.Text = "Add Singer";
            this.addButton.UseVisualStyleBackColor = false;
            this.addButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // removeButton
            // 
            this.removeButton.BackColor = System.Drawing.Color.RosyBrown;
            this.removeButton.Dock = System.Windows.Forms.DockStyle.Left;
            this.removeButton.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.removeButton.Location = new System.Drawing.Point(3, 60);
            this.removeButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.removeButton.Name = "removeButton";
            this.removeButton.Size = new System.Drawing.Size(224, 53);
            this.removeButton.TabIndex = 21;
            this.removeButton.Text = "Remove Singer";
            this.removeButton.UseVisualStyleBackColor = false;
            this.removeButton.Click += new System.EventHandler(this.removeButton_Click);
            // 
            // updateButton
            // 
            this.updateButton.BackColor = System.Drawing.Color.RosyBrown;
            this.updateButton.Dock = System.Windows.Forms.DockStyle.Left;
            this.updateButton.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.updateButton.Location = new System.Drawing.Point(3, 117);
            this.updateButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(224, 59);
            this.updateButton.TabIndex = 22;
            this.updateButton.Text = "Update Singer";
            this.updateButton.UseVisualStyleBackColor = false;
            this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 52.72136F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 47.27864F));
            this.tableLayoutPanel1.Controls.Add(this.ManagerLabel, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.SingerLabel, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.ManagersView, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.SingersView, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel3, 1, 2);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1231, 647);
            this.tableLayoutPanel1.TabIndex = 23;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 4;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.Controls.Add(this.NameLabel, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.SingerIdLabel, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.singerIdText, 1, 0);
            this.tableLayoutPanel2.Controls.Add(this.salaryText, 3, 3);
            this.tableLayoutPanel2.Controls.Add(this.ManagerIdLabel, 2, 0);
            this.tableLayoutPanel2.Controls.Add(this.SalaryLabel, 2, 3);
            this.tableLayoutPanel2.Controls.Add(this.managerIdText, 3, 0);
            this.tableLayoutPanel2.Controls.Add(this.voiceText, 1, 3);
            this.tableLayoutPanel2.Controls.Add(this.nameText, 1, 1);
            this.tableLayoutPanel2.Controls.Add(this.VoiceLabel, 0, 3);
            this.tableLayoutPanel2.Controls.Add(this.genreText, 3, 2);
            this.tableLayoutPanel2.Controls.Add(this.PhoneLabel, 2, 1);
            this.tableLayoutPanel2.Controls.Add(this.emailText, 1, 2);
            this.tableLayoutPanel2.Controls.Add(this.GenreLabel, 2, 2);
            this.tableLayoutPanel2.Controls.Add(this.phoneText, 3, 1);
            this.tableLayoutPanel2.Controls.Add(this.EmailLabel, 0, 2);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 467);
            this.tableLayoutPanel2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 4;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.Size = new System.Drawing.Size(642, 178);
            this.tableLayoutPanel2.TabIndex = 4;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 1;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel3.Controls.Add(this.updateButton, 0, 2);
            this.tableLayoutPanel3.Controls.Add(this.addButton, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.removeButton, 0, 1);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(651, 467);
            this.tableLayoutPanel3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 3;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel3.Size = new System.Drawing.Size(577, 178);
            this.tableLayoutPanel3.TabIndex = 5;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.MistyRose;
            this.ClientSize = new System.Drawing.Size(1231, 647);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.ManagersView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.SingersView)).EndInit();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            this.tableLayoutPanel3.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView ManagersView;
        private System.Windows.Forms.DataGridView SingersView;
        private System.Windows.Forms.Label ManagerLabel;
        private System.Windows.Forms.Label SingerLabel;
        private System.Windows.Forms.Label SingerIdLabel;
        private System.Windows.Forms.Label ManagerIdLabel;
        private System.Windows.Forms.Label NameLabel;
        private System.Windows.Forms.Label PhoneLabel;
        private System.Windows.Forms.Label EmailLabel;
        private System.Windows.Forms.Label GenreLabel;
        private System.Windows.Forms.Label VoiceLabel;
        private System.Windows.Forms.TextBox singerIdText;
        private System.Windows.Forms.TextBox managerIdText;
        private System.Windows.Forms.TextBox nameText;
        private System.Windows.Forms.TextBox phoneText;
        private System.Windows.Forms.TextBox emailText;
        private System.Windows.Forms.TextBox genreText;
        private System.Windows.Forms.TextBox voiceText;
        private System.Windows.Forms.Label SalaryLabel;
        private System.Windows.Forms.TextBox salaryText;
        private System.Windows.Forms.Button addButton;
        private System.Windows.Forms.Button removeButton;
        private System.Windows.Forms.Button updateButton;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
    }
}

