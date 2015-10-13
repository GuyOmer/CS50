<!DOCTYPE html>

<html>

    <head>

        <link href="/css/bootstrap.min.css" rel="stylesheet"/>
        <link href="/css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="/css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>C$50 Finance: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>C$50 Finance</title>
        <?php endif ?>

        <script src="/js/jquery-1.10.2.min.js"></script>
        <script src="/js/bootstrap.min.js"></script>
        <script src="/js/scripts.js"></script>

    </head>

    <body>

        <div class="container">

            <div id="top">
                <a href="/"><img alt="C$50 Finance" src="/img/logo.gif"/></a>
                <div>
                    <a class="text-center" href="index.php">Portfolio</a>
                    <a class="text-center" href="buy.php">Buy</a>
                    <a class="text-center" href="sell.php">Sell</a>
                    <a class="text-center" href="quote.php">Quote</a>
                    <a class="text-center" href="history.php">History</a>
                    <a class="text-center" href="logout.php"><strong>Logout</strong></a>
                </div>
            </div>
        
            <div id="middle">
