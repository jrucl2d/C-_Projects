using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Net.Security;
using System.Security.Cryptography.X509Certificates;

namespace Client
{
	public partial class Form1 : Form
	{
		public string serverIP = "127.0.0.1";
		public int port = 9876;
		public string serverDomain = "localhost";

		public Form1()
		{
			InitializeComponent();
		}

		private void button_Click(object sender, EventArgs e)
		{
			TcpClient client = new TcpClient(serverIP, port); // 클라이언트 객체
			SslStream sslStream = new SslStream(client.GetStream(), false, validateCertificate, null); // 클라이언트 스트림을 가져와서 SSL 덮어씌우기
			sslStream.AuthenticateAsClient(serverDomain);

			byte[] buf = Encoding.ASCII.GetBytes("Hello SSL!");
			sslStream.Write(buf, 0, buf.Length); // 서버로 전송
			sslStream.Flush(); // 다음을 위해 버퍼 비우기(에코 서버로부터 메시지 전달 받아야 하므로)

			buf = new byte[4096];
			int length = sslStream.Read(buf, 0, 4096);
			messageText.Text = Encoding.ASCII.GetString(buf, 0, length); // 에코 서버로부터 받은 메시지 출력
		}
		private bool validateCertificate(object sender, X509Certificate certificate, X509Chain chain, SslPolicyErrors sslPolicyErrors)
		{
			return true; // 인증서 오류없이 사설 인증서로 인증 테스트
		}
	}
}
