using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using time_tn.Properties;
using System.Text.RegularExpressions;

namespace time_tn
{
    public partial class frm_time_tn : Form
    {
        string[] DRAJ = new string[] { "", "درج", "درجين", "ربع", "أربعة", "خمسة", "نص", "سبعة", "أربعة", "ربع", "درجين", "درج", "" };
        string[] SEAA = new string[] { "نص الليل", "ماضي ساعة", "الساعتين", "ماضي تلاثة", "الأربعة", "الخمسة", "الستة", "السبعة", "الثمنية", "التسعة", "العشرة", "الحداش", "الأول" };
        int[] ZID_SEAA = new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 };
        string[] DRAJ_PREFIXE = new string[] { "", "و", "و", "و", "و", "و", "و", "و", "غير", "غير", "غير", "غير", "" };
        string[] KHAREJ_WALA_MA_HARRARCH = new string[] { "ما حررش", "ما حررش", "", "", "خارج", "خارج" };

        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HT_CAPTION = 0x2;

        [DllImportAttribute("user32.dll")] public static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);
        [DllImportAttribute("user32.dll")] public static extern bool ReleaseCapture();

        public frm_time_tn()
        {
            InitializeComponent();
        }

        private void lb_time_tn_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                ReleaseCapture();
                SendMessage(Handle, WM_NCLBUTTONDOWN, HT_CAPTION, 0);
            }
            else if (e.Button == MouseButtons.Right)
            {
                Application.Exit();
            }
            Settings.Default.WL = new Point(this.Location.X , this.Location.Y);
            Settings.Default.Width = this.Width;
        }

        private void frm_time_tn_Load(object sender, EventArgs e)
        {
            if (Settings.Default.WL!= null)
            {
                maj_display();
                this.Location = new Point(Settings.Default.WL.X - this.Width + Settings.Default.Width, Settings.Default.WL.Y);
            }
        }

        private void frm_time_tn_FormClosing(object sender, FormClosingEventArgs e)
        {
            Settings.Default.WL = new Point(this.Location.X , this.Location.Y);
            Settings.Default.Width = this.Width;
            Settings.Default.Save();
        }

        private void maj_display()
        {
            DateTime dt = DateTime.Now;
            int h = dt.Hour;
            int m = dt.Minute;
            int s = dt.Second;
            int drajj_tawa = ((m * 60) + s + 150) / 300;
            int kharej_wala_ma_harrarch_tawa = m - (drajj_tawa * 5) + 3;
            int heures_tawa = h + ZID_SEAA[drajj_tawa];
            if (heures_tawa != 12) { heures_tawa = (heures_tawa % 12); }

            string tn_seaa = SEAA[heures_tawa];
            string tn_prefixe_draj = DRAJ_PREFIXE[drajj_tawa];
            string tn_draj = DRAJ[drajj_tawa];
            string tn_kharej_wala_ma_harrarch = KHAREJ_WALA_MA_HARRARCH[kharej_wala_ma_harrarch_tawa];

            Regex trimmer = new Regex(@"\s\s+");
            string new_Time = trimmer.Replace(string.Concat(tn_seaa, " ", tn_prefixe_draj, " ", tn_draj, " ", tn_kharej_wala_ma_harrarch), " ");
            if (new_Time != lb_time_tn.Text)
            {
                int width_before_update = this.Width;
                lb_time_tn.Text = new_Time;
                int width_after_update = this.Width;
                this.Left -= (width_after_update - width_before_update);
            }
            
        }

        private void timer_timer_Tick(object sender, EventArgs e)
        {
            maj_display();
        }
    }
}
