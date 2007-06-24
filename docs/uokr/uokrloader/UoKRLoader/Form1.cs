using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Diagnostics;
using System.IO;

namespace UoKRLoader
{
    public partial class Form1 : Form
    {
        enum ENCRYPTION_PATCH_TYPE
        {
            None = 0,
            Login,
            Game,
            Both,

            End
        }

        private static string[] arrsEncryptio_Patch_Type = { "Yes", "Remove Login", "Remove Game", "Remove Both" };

        private class ConfigArgs
        {
            public uint uPort;
            public IPAddress ipHost;
            public ENCRYPTION_PATCH_TYPE encType;
        }

        public Form1()
        {
            InitializeComponent();

            this.cmbEncryption.SuspendLayout();
            this.cmbEncryption.Items.Clear();
            for (int i = 0; i < (int)ENCRYPTION_PATCH_TYPE.End; i++)
                this.cmbEncryption.Items.Add(arrsEncryptio_Patch_Type[i]);
            this.cmbEncryption.SelectedIndex = (int)ENCRYPTION_PATCH_TYPE.None;
            this.cmbEncryption.ResumeLayout();

            string tmpKrPath = Utility.GetExePath(Utility.UOKR_REGKEY);
            if (tmpKrPath != null)
            {
                this.txtUokrPath.Text = tmpKrPath;
            }

            if (File.Exists(Utility.LAUNCH_CFG))
            {
                string sConfig = null;

                using (StreamReader srRead = File.OpenText(Utility.LAUNCH_CFG))
                {
                    sConfig = srRead.ReadToEnd();
                }

                if ((sConfig != null) && (sConfig.Length != 0))
                {
                    sConfig = sConfig.Trim();
                    string[] sValues = sConfig.Split(new char[]{','});
                    this.txtIptopatch.Text = sValues[0].Trim();
                    this.nudPort.Value = Int32.Parse(sValues[1].Trim());
                    // -------------------------------------------------
                    this.cmbEncryption.SuspendLayout();
                    ENCRYPTION_PATCH_TYPE iSelected = (ENCRYPTION_PATCH_TYPE)Int32.Parse(sValues[2].Trim());
                    if (iSelected == ENCRYPTION_PATCH_TYPE.End)
                        iSelected = ENCRYPTION_PATCH_TYPE.None;
                    this.cmbEncryption.SelectedIndex = (int)iSelected;
                    this.cmbEncryption.ResumeLayout();
                }
            }
        }

        private void btnAbout_Click(object sender, EventArgs e)
        {
            Form2 frmAbout = new Form2();
            DialogResult drResult = frmAbout.ShowDialog(this);
            if (drResult == DialogResult.OK)
            {
                frmAbout.Close();
            }
            else
            {
                Close();
            }
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            DialogResult drOpenFile = ofdUOKRClient.ShowDialog(this);

            if (drOpenFile == DialogResult.OK)
            {
                this.txtUokrPath.Text = ofdUOKRClient.FileName.Substring(0, ofdUOKRClient.FileName.LastIndexOf('\\'));
            }
        }

        private void btnLaunch_Click(object sender, EventArgs e)
        {
            PathOrLaunch(false, ParseConfig());
        }

        private void btnPatch_Click(object sender, EventArgs e)
        {
            DialogResult drMessage = MessageBox.Show("This will create a patched client called " + Utility.UOKR_PATCHCLIENT + " in the selected dir.\nDo you want to continue?", "Patch Information", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if ( drMessage == DialogResult.Yes )
                PathOrLaunch(true, ParseConfig());
        }

        private ConfigArgs ParseConfig()
        {
            if (nudPort.Value <= 0 || nudPort.Value > 65535)
            {
                MessageBox.Show("Invalid port: " + nudPort.Value.ToString() + " !", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return null;
            }

            IPHostEntry host;

            try
            {
                host = Dns.GetHostEntry(txtIptopatch.Text.Trim());
            }
            catch (Exception)
            {
                MessageBox.Show("Invalid ip: " + txtIptopatch.Text + " !", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return null;
            }

            IPAddress ip = host.AddressList[0];

            if (this.ckbRemind.Checked)
            {
                if (this.txtIptopatch.Text.Length > 0)
                {
                    using (StreamWriter srRead = File.CreateText(Utility.LAUNCH_CFG))
                    {
                        srRead.Write(this.txtIptopatch.Text.Trim() + "," + this.nudPort.Value.ToString() + "," + this.cmbEncryption.SelectedIndex.ToString());
                    }
                }
            }

            ConfigArgs caTouse = new ConfigArgs();
            caTouse.uPort = (uint)this.nudPort.Value;
            caTouse.ipHost = ip;
            caTouse.encType = (ENCRYPTION_PATCH_TYPE)this.cmbEncryption.SelectedIndex;

            return caTouse;
        }

        private void PathOrLaunch(bool bPatch, ConfigArgs caTouse)
        {
            if (caTouse == null)
                return;

            byte[] newData = new byte[Utility.UOKR_IPDATA.Length];
            Utility.UOKR_IPDATA.CopyTo(newData, 0);
            newData[1] = caTouse.ipHost.GetAddressBytes()[3];
            newData[3] = caTouse.ipHost.GetAddressBytes()[1];
            newData[8] = caTouse.ipHost.GetAddressBytes()[0];
            newData[14] = caTouse.ipHost.GetAddressBytes()[2];
            newData[24] = (byte)(caTouse.uPort & 0xFF);
            newData[25] = (byte)((caTouse.uPort & 0xFF00) >> 8);
            newData[30] = (byte)(caTouse.uPort & 0xFF);
            newData[31] = (byte)((caTouse.uPort & 0xFF00) >> 8);

            int iResultEncLogin = 0;
            int iResultEncGame = 0;
            int iResultIP = 0;
            ENCRYPTION_PATCH_TYPE encType = caTouse.encType;

            // !bPatch
            Process prcTostart = null;
            // bPatch
            FileStream fsToPatch = null;

            if (!bPatch)
            {
                prcTostart = new Process();
                prcTostart.StartInfo.FileName = this.txtUokrPath.Text + @"\" + Utility.UOKR_CLIENT;
                prcTostart.StartInfo.WorkingDirectory = this.txtUokrPath.Text;

                if (!prcTostart.Start())
                {
                    MessageBox.Show("Cannot start the client !", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
            }
            else
            {
                try
                {
                    File.Copy(this.txtUokrPath.Text + @"\" + Utility.UOKR_CLIENT, this.txtUokrPath.Text + @"\" + Utility.UOKR_PATCHCLIENT, true);
                }
                catch (Exception)
                {
                    MessageBox.Show("Cannot create file " + this.txtUokrPath.Text + @"\" + Utility.UOKR_PATCHCLIENT + " !", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                try
                {
                    fsToPatch = File.Open(this.txtUokrPath.Text + @"\" + Utility.UOKR_PATCHCLIENT,FileMode.Open,FileAccess.ReadWrite);
                }
                catch (Exception)
                {
                    MessageBox.Show("Cannot open file " + this.txtUokrPath.Text + @"\" + Utility.UOKR_PATCHCLIENT + " !", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
            }

            Stream strGeneric;
            if (bPatch)
            {
                strGeneric = fsToPatch;
            }
            else
            {
                strGeneric = new ProcessStream((IntPtr)prcTostart.Id);
            }

            iResultIP = Utility.Search(strGeneric, Utility.UOKR_IPDATA, bPatch);
            if (iResultIP == 0)
            {
                strGeneric.Close();
                if (!bPatch)
                    prcTostart.Close();

                MessageBox.Show("Cannot patch IP on the client !", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if ((encType == ENCRYPTION_PATCH_TYPE.Login) || (encType == ENCRYPTION_PATCH_TYPE.Both))
            {
                iResultEncLogin = Utility.Search(strGeneric, Utility.UOKR_LOGDATA, bPatch);
                if (iResultEncLogin == 0)
                {
                    strGeneric.Close();
                    if (!bPatch)
                        prcTostart.Close();

                    MessageBox.Show("Cannot patch Login Encryption on the client !", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
            }

            if ((encType == ENCRYPTION_PATCH_TYPE.Game) || (encType == ENCRYPTION_PATCH_TYPE.Both))
            {
                iResultEncGame = Utility.Search(strGeneric, Utility.UOKR_ENCDATA, bPatch);
                if (iResultEncGame == 0)
                {
                    strGeneric.Close();
                    if (!bPatch)
                        prcTostart.Close();

                    MessageBox.Show("Cannot patch Game Encryption on the client !", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
            }

            if (bPatch)
            {
                strGeneric.Seek(0, SeekOrigin.Begin);
            }

            strGeneric.Seek(iResultIP, SeekOrigin.Begin);
            strGeneric.Write(newData, 0, newData.Length);

            if ((encType == ENCRYPTION_PATCH_TYPE.Login) || (encType == ENCRYPTION_PATCH_TYPE.Both))
            {
                strGeneric.Seek(iResultEncLogin, SeekOrigin.Begin);
                strGeneric.Write(Utility.UOKR_LOGPATCHDATA, 0, Utility.UOKR_LOGPATCHDATA.Length);
            }
            if ((encType == ENCRYPTION_PATCH_TYPE.Game) || (encType == ENCRYPTION_PATCH_TYPE.Both))
            {

                strGeneric.Seek(iResultEncGame, SeekOrigin.Begin);
                strGeneric.Write(Utility.UOKR_ENCPATCHDATA, 0, Utility.UOKR_ENCPATCHDATA.Length);
            }

            strGeneric.Close();

            if (!bPatch)
            {
                System.Threading.Thread.Sleep(10);
                Close();
            }
            else
            {
                this.ckbRemind.Checked = false;
                MessageBox.Show("Client " + this.txtUokrPath.Text + @"\" + Utility.UOKR_PATCHCLIENT + " succesfully patched.", "Patch Done", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }
    }
}