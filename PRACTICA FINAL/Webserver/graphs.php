<?php
    $connection2 = mysqli_connect('localhost', 'root', '', 'registrossmartroom');
?>

<!DOCTYPE html>
<html>
<head>
    <meta charset='utf-8'>
    <meta http-equiv='X-UA-Compatible' content='IE=edge'>
    <title>Smart Room</title>
    <meta name='viewport' content='width=device-width, initial-scale=1'>
    <link rel='stylesheet' type='text/css' media='screen' href='index.css'>
</head>
<body>

    <!-- Navigation -->

    <div class="container">
        <div class="navigation">
            <ul>
                <li>
                    <a href="index.php">
                        <span class="icon"> <ion-icon name="medkit-outline"></ion-icon> </span>
                        <span class="title"> Smart Room </span>
                    </a>
                </li>
                <li>
                    <a href="index.php">
                        <span class="icon"> <ion-icon name="home-outline"></ion-icon> </span>
                        <span class="title"> Datos </span>
                    </a>
                </li>
                <li>
                    <a href="graphs.php">
                        <span class="icon"> <ion-icon name="stats-chart-outline"></ion-icon> </span>
                        <span class="title"> Gráficas </span>
                    </a>
                </li>
            </ul>
        </div>
    </div>

    <!-- Main -->

    <div class="main">
        <div class="topbar">
            <div class="toggle">
                <ion-icon name="menu-outline"></ion-icon>
            </div>
        </div>

        <!-- Cards -->

        <?php
        $sql3 = "SELECT id, humedad, temperatura FROM registros ORDER BY id DESC LIMIT 1";
        $result = mysqli_query($connection2, $sql3);
        
        $row = mysqli_fetch_array($result);
            
        ?>

        <div class="cardBox">
            <div class="card">
                <div>
                    <div class="numbers"> <?php echo $row['temperatura'] ?>°C </div>
                    <div class="cardName"> temperatura </div>
                </div>
                <div class="iconBx">
                    <ion-icon name="thermometer-outline"></ion-icon>
                </div>
            </div>

            <div class="card">
                <div>
                    <div class="numbers"> <?php echo $row['humedad'] ?>% </div>
                    <div class="cardName"> Humedad </div>
                </div>
                <div class="iconBx">
                    <ion-icon name="water-outline"></ion-icon>
                </div>
            </div>
        </div>

        <?php
        
        ?>

        <!-- Charts -->

        <div class="chartsBox">
            <div class="chart">
                <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1529977/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15"></iframe>
            </div>

            <div class="chart">
                <iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1529977/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15"></iframe>
            </div>
        </div>

        
    </div>

</body>

<script type="module" src="https://unpkg.com/ionicons@5.5.2/dist/ionicons/ionicons.esm.js"></script>
<script nomodule src="https://unpkg.com/ionicons@5.5.2/dist/ionicons/ionicons.js"></script>

<script src="main.js"></script>

</html>