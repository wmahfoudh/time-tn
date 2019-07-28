namespace time_tn
{
    partial class frm_time_tn
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
            this.components = new System.ComponentModel.Container();
            this.lb_time_tn = new System.Windows.Forms.Label();
            this.timer_timer = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // lb_time_tn
            // 
            this.lb_time_tn.AutoSize = true;
            this.lb_time_tn.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lb_time_tn.Cursor = System.Windows.Forms.Cursors.Default;
            this.lb_time_tn.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lb_time_tn.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.lb_time_tn.Font = new System.Drawing.Font("Noto Kufi Arabic", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lb_time_tn.Location = new System.Drawing.Point(0, 0);
            this.lb_time_tn.Margin = new System.Windows.Forms.Padding(6);
            this.lb_time_tn.Name = "lb_time_tn";
            this.lb_time_tn.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.lb_time_tn.Size = new System.Drawing.Size(25, 38);
            this.lb_time_tn.TabIndex = 0;
            this.lb_time_tn.Text = "-";
            this.lb_time_tn.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.lb_time_tn.MouseClick += new System.Windows.Forms.MouseEventHandler(this.lb_time_tn_MouseClick);
            this.lb_time_tn.MouseDown += new System.Windows.Forms.MouseEventHandler(this.lb_time_tn_MouseDown);
            // 
            // timer_timer
            // 
            this.timer_timer.Enabled = true;
            this.timer_timer.Interval = 1000;
            this.timer_timer.Tick += new System.EventHandler(this.timer_timer_Tick);
            // 
            // frm_time_tn
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 28F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.BackColor = System.Drawing.Color.Gold;
            this.ClientSize = new System.Drawing.Size(117, 45);
            this.ControlBox = false;
            this.Controls.Add(this.lb_time_tn);
            this.Font = new System.Drawing.Font("Noto Kufi Arabic", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Margin = new System.Windows.Forms.Padding(6);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "frm_time_tn";
            this.ShowInTaskbar = false;
            this.TopMost = true;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frm_time_tn_FormClosing);
            this.Load += new System.EventHandler(this.frm_time_tn_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lb_time_tn;
        private System.Windows.Forms.Timer timer_timer;
    }
}

