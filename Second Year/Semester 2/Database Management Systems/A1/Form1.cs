using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace A1
{
    public partial class Form1 : Form
    {
        private SqlConnection dbConnection;
        private SqlDataAdapter daManagers, daSingers;
        private DataSet tableData;
        private DataRelation drManagerSinger;
        BindingSource bsManagers, bsSingers;

        public Form1()
        {
            InitializeComponent();
        }

        private void ReloadSingersTableView()
        {
            if (tableData.Tables["Singer"] != null)
            {
                tableData.Tables["Singer"].Clear();
            }
            daSingers.Fill(tableData, "Singer");
            SingersView.DataSource = bsSingers;
        }

        private void ManagersView_SelectionChanged(object sender, EventArgs e)
        {
            singerIdText.Clear();
            managerIdText.Clear();
            nameText.Clear();
            phoneText.Clear();
            emailText.Clear();
            genreText.Clear();
            voiceText.Clear();
            salaryText.Clear();
            if (ManagersView.SelectedRows.Count != 0)
            {
                DataGridViewRow selectedRow = ManagersView.SelectedRows[0];
                daSingers.SelectCommand = new SqlCommand("SELECT * FROM Singer WHERE manager_id = " + selectedRow.Cells[0].Value, dbConnection);
                ReloadSingersTableView();
            }
        }

        private void SingersView_SelectionChanged(object sender, EventArgs e)
        {
            if (SingersView.SelectedRows.Count != 0)
            {
                DataGridViewRow selectedRow = SingersView.SelectedRows[0];
                singerIdText.Text = selectedRow.Cells[0].Value.ToString();
                managerIdText.Text = selectedRow.Cells[1].Value.ToString();
                nameText.Text = selectedRow.Cells[2].Value.ToString();
                phoneText.Text = selectedRow.Cells[3].Value.ToString();
                emailText.Text = selectedRow.Cells[4].Value.ToString();
                genreText.Text = selectedRow.Cells[5].Value.ToString();
                voiceText.Text = selectedRow.Cells[6].Value.ToString();
                salaryText.Text = selectedRow.Cells[7].Value.ToString();
            }
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            SqlCommand command = new SqlCommand("INSERT INTO Singer (singer_id, manager_id, singer_name, singer_phone_number, singer_email, prefered_genre, type_of_voice, singer_salary) " +
                "VALUES (@SingerID, @ManagerID, @SingerName, @SingerPhoneNumber, @SingerEmail, @PreferedGenre, @TypeOfVoice, @SingerSalary)", dbConnection);
            if (singerIdText.Text.Length != 0)
            {
                try
                {
                    int singer_id = Int32.Parse(singerIdText.Text);
                    if (managerIdText.Text.Length != 0)
                    {
                        int manager_id = Int32.Parse(managerIdText.Text);
                        int salary;
                        if (salaryText.Text.Length != 0)
                            salary = Int32.Parse(salaryText.Text);
                        else
                            salary = 0;
                        command.Parameters.Add("@SingerID", SqlDbType.Int);
                        command.Parameters["@SingerID"].Value = singer_id;
                        command.Parameters.Add("@ManagerID", SqlDbType.Int);
                        command.Parameters["@ManagerID"].Value = manager_id;
                        command.Parameters.Add("@SingerName", SqlDbType.VarChar, 50);
                        command.Parameters["@SingerName"].Value = nameText.Text;
                        command.Parameters.Add("@SingerPhoneNumber", SqlDbType.VarChar, 10);
                        command.Parameters["@SingerPhoneNumber"].Value = phoneText.Text;
                        command.Parameters.Add("@SingerEmail", SqlDbType.VarChar, 50);
                        command.Parameters["@SingerEmail"].Value = emailText.Text;
                        command.Parameters.Add("@PreferedGenre", SqlDbType.VarChar, 25);
                        command.Parameters["@PreferedGenre"].Value = genreText.Text;
                        command.Parameters.Add("@TypeOfVoice", SqlDbType.VarChar, 25);
                        command.Parameters["@TypeOfVoice"].Value = voiceText.Text;
                        command.Parameters.Add("@SingerSalary", SqlDbType.Int);
                        command.Parameters["@SingerSalary"].Value = salary;
                        try
                        {
                            daSingers.InsertCommand = command;
                            daSingers.InsertCommand.ExecuteNonQuery();
                            ReloadSingersTableView();
                        }
                        catch (SqlException sqlException)
                        {
                            if (sqlException.Number == 2627)
                                MessageBox.Show("The singer id, phone number and email must be unique!");
                            else if (sqlException.Number == 547)
                                MessageBox.Show("There's no manager with the given id!");
                            else
                                MessageBox.Show(sqlException.Message);
                        }
                    }
                    else
                        MessageBox.Show("Please provide a manager id!");
                } catch (FormatException ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
            else
                MessageBox.Show("Please provide a singer id!");
        }

        private void removeButton_Click(object sender, EventArgs e)
        {
            SqlCommand command = new SqlCommand("DELETE FROM Singer WHERE singer_id = @SingerID", dbConnection);
            if (singerIdText.Text.Length != 0)
            {
                int singer_id = Int32.Parse(singerIdText.Text);
                command.Parameters.Add("@SingerID", SqlDbType.Int);
                command.Parameters["@SingerID"].Value = singer_id;
                try
                {
                    daSingers.DeleteCommand = command;
                    int numberOfDeletedSingers = daSingers.DeleteCommand.ExecuteNonQuery();
                    if (numberOfDeletedSingers == 0)
                    {
                        MessageBox.Show("There is no singer with the given id!");
                    }
                    else
                    {
                        ReloadSingersTableView();
                    }
                }
                catch (SqlException sqlException)
                {
                    MessageBox.Show(sqlException.ToString());
                }
            }
            else
                MessageBox.Show("Please provide a singer id!");
        }

        private void SingersView_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {
            if (e.Exception is InvalidConstraintException)
                MessageBox.Show("The manager id you provided does not exist!");
            else if (e.Exception is FormatException)
                MessageBox.Show(e.Exception.Message);
            else
                try
                {
                    throw e.Exception;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            /*
            SqlCommand command = new SqlCommand("UPDATE Singer " +
                "SET manager_id = @ManagerID, singer_name = @SingerName, singer_phone_number = @SingerPhoneNumber, " +
                "singer_email = @SingerEmail, prefered_genre = @PreferedGenre, type_of_voice = @TypeOfVoice, singer_salary = @SingerSalary " +
                "WHERE singer_id = @SingerID", dbConnection);
            int singer_id = Int32.Parse(singerIdText.Text);
            int manager_id = Int32.Parse(managerIdText.Text);
            int salary = Int32.Parse(salaryText.Text);
            command.Parameters.Add("@SingerID", SqlDbType.Int);
            command.Parameters["@SingerID"].Value = singer_id;
            command.Parameters.Add("@ManagerID", SqlDbType.Int);
            command.Parameters["@ManagerID"].Value = manager_id;
            command.Parameters.Add("@SingerName", SqlDbType.VarChar, 50);
            command.Parameters["@SingerName"].Value = nameText.Text;
            command.Parameters.Add("@SingerPhoneNumber", SqlDbType.VarChar, 10);
            command.Parameters["@SingerPhoneNumber"].Value = phoneText.Text;
            command.Parameters.Add("@SingerEmail", SqlDbType.VarChar, 50);
            command.Parameters["@SingerEmail"].Value = emailText.Text;
            command.Parameters.Add("@PreferedGenre", SqlDbType.VarChar, 25);
            command.Parameters["@PreferedGenre"].Value = genreText.Text;
            command.Parameters.Add("@TypeOfVoice", SqlDbType.VarChar, 25);
            command.Parameters["@TypeOfVoice"].Value = voiceText.Text;
            command.Parameters.Add("@SingerSalary", SqlDbType.Int);
            command.Parameters["@SingerSalary"].Value = salary;
            try
            {
                daSingers.UpdateCommand = command;
                int numberOfUpdatedSingers = daSingers.UpdateCommand.ExecuteNonQuery();
                if (numberOfUpdatedSingers != 0)
                {
                    ReloadSingersTableView();
                } else
                {
                    MessageBox.Show("There is no singer with the given id!");
                }
            }
            catch (SqlException sqlException)
            {
                if (sqlException.Number == 2627)
                    MessageBox.Show("The singer id, phone number and email must be unique!");
                else if (sqlException.Number == 547)
                    MessageBox.Show("There's no manager with the given id!");
                else
                    MessageBox.Show(sqlException.Message);
            }
            */
            SqlCommandBuilder builder = new SqlCommandBuilder(daSingers);
            daSingers.UpdateCommand = builder.GetUpdateCommand();
            try
            {
                daSingers.Update(tableData, "Singer");
            } catch (SqlException sqlException)
            {
                if (sqlException.Number == 2627)
                    MessageBox.Show("The singer id, phone number and email must be unique!");
                else if (sqlException.Number == 547)
                    MessageBox.Show("There's no manager with the given id!");
                else
                    MessageBox.Show(sqlException.Message);
            }
            ReloadSingersTableView();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            dbConnection = new SqlConnection("Server=DESKTOP-S6C1A6M;Database=Music_Production_Company;Trusted_Connection=true");
            dbConnection.Open();

            daManagers = new SqlDataAdapter("SELECT * FROM Manager", dbConnection);
            tableData = new DataSet();
            daManagers.Fill(tableData, "Manager");
            ManagersView.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            daSingers = new SqlDataAdapter("SELECT * FROM Singer", dbConnection);
            daSingers.Fill(tableData, "Singer");
            SingersView.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            DataColumn managerIdManager = tableData.Tables["Manager"].Columns["manager_id"];
            DataColumn managerIdSinger = tableData.Tables["Singer"].Columns["manager_id"];
            drManagerSinger = new DataRelation("FK_MANAGER_SINGER", managerIdManager, managerIdSinger);
            tableData.Relations.Add(drManagerSinger);

            bsManagers = new BindingSource();
            bsManagers.DataSource = tableData;
            bsManagers.DataMember = "Manager";

            bsSingers = new BindingSource();
            bsSingers.DataSource = bsManagers;
            bsSingers.DataMember = "FK_MANAGER_SINGER";
            ManagersView.DataSource = bsManagers;
        }
    }
}
