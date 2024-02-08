<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> Partial Class Form1
#Region "Windows Form Designer generated code "
	<System.Diagnostics.DebuggerNonUserCode()> Public Sub New()
		MyBase.New()
		'This call is required by the Windows Form Designer.
		InitializeComponent()
	End Sub
	'Form overrides dispose to clean up the component list.
	<System.Diagnostics.DebuggerNonUserCode()> Protected Overloads Overrides Sub Dispose(ByVal Disposing As Boolean)
		If Disposing Then
			If Not components Is Nothing Then
				components.Dispose()
			End If
		End If
		MyBase.Dispose(Disposing)
	End Sub
	'Required by the Windows Form Designer
	Private components As System.ComponentModel.IContainer
	Public ToolTip1 As System.Windows.Forms.ToolTip
	Public WithEvents Command1 As System.Windows.Forms.Button
	Public WithEvents Message As System.Windows.Forms.TextBox
	Public WithEvents Timer1 As System.Windows.Forms.Timer
	Public WithEvents RtS As System.Windows.Forms.Button
	Public WithEvents Off As System.Windows.Forms.Button
	Public WithEvents WaitLight As System.Windows.Forms.Label
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
	<System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.Command1 = New System.Windows.Forms.Button()
        Me.Message = New System.Windows.Forms.TextBox()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.RtS = New System.Windows.Forms.Button()
        Me.Off = New System.Windows.Forms.Button()
        Me.WaitLight = New System.Windows.Forms.Label()
        Me.Autolaunch = New System.Windows.Forms.CheckBox()
        Me.RunWinappBackgroundWorker = New System.ComponentModel.BackgroundWorker()
        Me.SuspendLayout()
        '
        'Command1
        '
        Me.Command1.BackColor = System.Drawing.SystemColors.Control
        Me.Command1.Cursor = System.Windows.Forms.Cursors.Default
        Me.Command1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Command1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Command1.Location = New System.Drawing.Point(48, 224)
        Me.Command1.Name = "Command1"
        Me.Command1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Command1.Size = New System.Drawing.Size(17, 19)
        Me.Command1.TabIndex = 4
        Me.Command1.Text = "O"
        Me.Command1.UseVisualStyleBackColor = False
        '
        'Message
        '
        Me.Message.AcceptsReturn = True
        Me.Message.BackColor = System.Drawing.SystemColors.Window
        Me.Message.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.Message.Enabled = False
        Me.Message.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Message.ForeColor = System.Drawing.SystemColors.WindowText
        Me.Message.Location = New System.Drawing.Point(0, 368)
        Me.Message.MaxLength = 0
        Me.Message.Name = "Message"
        Me.Message.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Message.Size = New System.Drawing.Size(113, 20)
        Me.Message.TabIndex = 2
        '
        'Timer1
        '
        Me.Timer1.Interval = 500
        '
        'RtS
        '
        Me.RtS.BackColor = System.Drawing.SystemColors.Control
        Me.RtS.Cursor = System.Windows.Forms.Cursors.Default
        Me.RtS.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.RtS.ForeColor = System.Drawing.SystemColors.ControlText
        Me.RtS.Location = New System.Drawing.Point(8, 328)
        Me.RtS.Name = "RtS"
        Me.RtS.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.RtS.Size = New System.Drawing.Size(97, 33)
        Me.RtS.TabIndex = 1
        Me.RtS.Text = "Start"
        Me.RtS.UseVisualStyleBackColor = False
        '
        'Off
        '
        Me.Off.BackColor = System.Drawing.SystemColors.Control
        Me.Off.Cursor = System.Windows.Forms.Cursors.Default
        Me.Off.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Off.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Off.Location = New System.Drawing.Point(8, 288)
        Me.Off.Name = "Off"
        Me.Off.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Off.Size = New System.Drawing.Size(97, 33)
        Me.Off.TabIndex = 0
        Me.Off.Text = "Off"
        Me.Off.UseVisualStyleBackColor = False
        '
        'WaitLight
        '
        Me.WaitLight.BackColor = System.Drawing.Color.Silver
        Me.WaitLight.Cursor = System.Windows.Forms.Cursors.Default
        Me.WaitLight.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.WaitLight.ForeColor = System.Drawing.Color.FromArgb(CType(CType(128, Byte), Integer), CType(CType(128, Byte), Integer), CType(CType(128, Byte), Integer))
        Me.WaitLight.Location = New System.Drawing.Point(40, 208)
        Me.WaitLight.Name = "WaitLight"
        Me.WaitLight.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.WaitLight.Size = New System.Drawing.Size(35, 13)
        Me.WaitLight.TabIndex = 3
        Me.WaitLight.Text = "WAIT"
        Me.WaitLight.TextAlign = System.Drawing.ContentAlignment.TopCenter
        '
        'Autolaunch
        '
        Me.Autolaunch.AutoSize = True
        Me.Autolaunch.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Autolaunch.Location = New System.Drawing.Point(35, 392)
        Me.Autolaunch.Name = "Autolaunch"
        Me.Autolaunch.Size = New System.Drawing.Size(85, 18)
        Me.Autolaunch.TabIndex = 6
        Me.Autolaunch.Text = "Auto-launch"
        Me.Autolaunch.UseVisualStyleBackColor = True
        '
        'RunWinappBackgroundWorker
        '
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 14.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.Control
        Me.ClientSize = New System.Drawing.Size(116, 413)
        Me.Controls.Add(Me.Autolaunch)
        Me.Controls.Add(Me.Command1)
        Me.Controls.Add(Me.Message)
        Me.Controls.Add(Me.RtS)
        Me.Controls.Add(Me.Off)
        Me.Controls.Add(Me.WaitLight)
        Me.Cursor = System.Windows.Forms.Cursors.Default
        Me.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Location = New System.Drawing.Point(4, 23)
        Me.Name = "Form1"
        Me.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Text = "RtsSim"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Autolaunch As System.Windows.Forms.CheckBox
    Friend WithEvents RunWinappBackgroundWorker As System.ComponentModel.BackgroundWorker
#End Region
End Class