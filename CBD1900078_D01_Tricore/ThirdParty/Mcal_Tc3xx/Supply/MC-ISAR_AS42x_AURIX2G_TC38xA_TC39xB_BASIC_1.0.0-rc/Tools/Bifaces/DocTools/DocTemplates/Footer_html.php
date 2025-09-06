<!-- start footer part -->
<?php $info= $this->infoSourceObject; 
$version= "Vx.y.z";
$status= "Draft/Release";
$type= "MC User Manual/Application Note";
$control= "Internal";
$issue= "Mmm YYYY";
if($info->logisticData['version'] !== Null)
{
	$version= $info->logisticData['version'];
}
if($info->logisticData['status'] !== Null)
{
	$status= $info->logisticData['status'];
}
if($info->logisticData['type'] !== Null)
{
	$type= $info->logisticData['type'];
}
if($info->logisticData['control'] !== Null)
{
	$control= $info->logisticData['control'];
}
if($info->logisticData['issuemonth'] !== Null)
{
	$issuemonth= $info->logisticData['issuemonth'];
}
if($info->logisticData['issueyear'] !== Null)
{
	$issueyear= $info->logisticData['issueyear'];
}
?>
<hr class="footer"/>
<table class="footer" cellspacing="0" cellpadding="0" style="borderwidth:100%;">
	<tr>
		<td align="left" style="padding-left: 1.5em; width:30%;">
			<div class="footer"><?php echo $type?></div>
			<div class="footer"><?php echo $status?></div>
		</td>
		
		<td align="middle" style="padding-left: 0.5em; padding-right: 0.5em; width:40%;">
				<div class="copyright">Copyright &copy; Infineon Technologies AG <?php echo $issueyear?></div>
				<a class="copyright" href="http://www.infineon.com" style="color: blue;">www.infineon.com</a>
		</td>
		<td align="right" style="padding-right: 1.5em; width:30%;">
			<div class="footer"><?php echo $version?></div>
			<div class="footer"><?php echo $issuemonth?> <?php echo $issueyear?></div>
		</td>
	</tr>
</table>
</body>
</html>
 