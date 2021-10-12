<?php
    $connection = mysqli_connect('localhost', 'root', '', 'registrosmart');
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
                    <a href="index.php" class='tituloPagina'>
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
        $sql2 = "SELECT id, humedad, temperatura FROM registros ORDER BY id DESC LIMIT 1";
        $result = mysqli_query($connection, $sql2);
        
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

        <!-- Table -->

        <div class="details">
            <div class="recentMeasures">
                <div class="cardHeader">
                    <h2>Medidas recientes</h2>
                </div>
                <table>
                    <thead>
                        <tr>
                            <td>ID</td>
                            <td>Fecha - Hora</td>
                            <td>Temperatura</td>
                            <td>Humedad</td>
                            <td>Bombillo</td>
                            <td>Ventilador</td>
                        </tr>
                    </thead>
                    <tbody>
                        <?php
                        $sql2 = "SELECT * FROM registros ORDER BY id DESC LIMIT 10";
                        $result = mysqli_query($connection, $sql2);

                        while($mostrar = mysqli_fetch_array($result)){
                        ?>

                        <tr>
                            <td> <?php echo $mostrar['id'] ?> </td>
                            <td> <?php echo $mostrar['hora'] ?> </td>
                            <td> <?php echo $mostrar['temperatura'] ?>°C </td>
                            <td> <?php echo $mostrar['humedad'] ?> %</td>
                            <td> <?php echo $mostrar['bombillo'] ?> </td>
                            <td> <?php echo $mostrar['ventilador'] ?> </td>
                        </tr>

                        <?php
                        }
                        ?>

                    </tbody>
                </table>
            </div>
        </div>
    </div>

    <!-- Charts -->



</body>

<script type="module" src="https://unpkg.com/ionicons@5.5.2/dist/ionicons/ionicons.esm.js"></script>
<script nomodule src="https://unpkg.com/ionicons@5.5.2/dist/ionicons/ionicons.js"></script>

<script src="main.js"></script>

</html>