namespace show
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.textBox_in = new System.Windows.Forms.TextBox();
            this.button_search = new System.Windows.Forms.Button();
            this.textBox_out = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // textBox_in
            // 
            this.textBox_in.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox_in.Location = new System.Drawing.Point(12, 12);
            this.textBox_in.Multiline = true;
            this.textBox_in.Name = "textBox_in";
            this.textBox_in.Size = new System.Drawing.Size(273, 180);
            this.textBox_in.TabIndex = 1;
            this.textBox_in.Text = "在此输入关键词（以;分隔）.";
            // 
            // button_search
            // 
            this.button_search.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_search.Location = new System.Drawing.Point(301, 9);
            this.button_search.Name = "button_search";
            this.button_search.Size = new System.Drawing.Size(268, 40);
            this.button_search.TabIndex = 2;
            this.button_search.Text = "搜索";
            this.button_search.UseVisualStyleBackColor = true;
            this.button_search.Click += new System.EventHandler(this.button_search_Click);
            // 
            // textBox_out
            // 
            this.textBox_out.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.textBox_out.Location = new System.Drawing.Point(301, 55);
            this.textBox_out.Multiline = true;
            this.textBox_out.Name = "textBox_out";
            this.textBox_out.Size = new System.Drawing.Size(268, 137);
            this.textBox_out.TabIndex = 3;
            this.textBox_out.Text = "在此输出与输入关键词联系最紧密的关键词.";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(581, 205);
            this.Controls.Add(this.textBox_out);
            this.Controls.Add(this.button_search);
            this.Controls.Add(this.textBox_in);
            this.Name = "Form1";
            this.Text = "Show";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox_in;
        private System.Windows.Forms.Button button_search;
        private System.Windows.Forms.TextBox textBox_out;
    }
}

