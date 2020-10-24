﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client
{
	public partial class MenuForm : Form
	{
		public MenuForm()
		{
			InitializeComponent();
		}

		private void singleButton_Click(object sender, EventArgs e)
		{
			Hide();
			SinglePlayForm singlePlayForm = new SinglePlayForm();
			singlePlayForm.FormClosed += new FormClosedEventHandler(childForm_Closed); // Single Play Form이 닫히면 기존의 메뉴 Form 화면이 나옴
			singlePlayForm.Show();
		}

		private void exitButton_Click(object sender, EventArgs e)
		{
			System.Windows.Forms.Application.Exit();
		}
		void childForm_Closed(object sender, FormClosedEventArgs e)
		{
			Show();
		}
	}
}
