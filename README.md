<p>The TyBank admin only functions as the creator of a <a href="https://github.com/markytools/tybankonline">TyBank</a> online account.</p>
<p><span style="text-decoration: underline;"><strong>Requirements:</strong></span></p>
<ul>
<li>An online database should be setup, so use the TyBank database sql file to import the TyBank database tables into the online MySQL database, and remember to replace line 10 &ldquo;USE database_name;&rdquo; of that file with your database name (You can use phpMyAdmin to import this file)</li>
</ul>
<p>(Note: The database setting is configured to use our free heliohost database, but if you want to create your own database, you can change the configs on your own at the sqldatabase.cpp file)</p>
<ul>
<li>Replace MC_DIRECTORY, ACCT_FILE, and RECORDS_DIR in the datahandler.h with the corresponding mastercard folder, records folder, and acct.lst file, which is usually located at the root level of the app code</li>
<li>Make sure to have the mySQL qt connector installed</li>
</ul>
<p>&nbsp;</p>
<p><span style="text-decoration: underline;"><strong>General Usage:</strong></span></p>
<ul>
<li>Only the first function, New/Existing Account, is the only relevant task that can be done using the TyBank admin. One person can have multiple bank accounts (multiple account numbers), which is the reason for having the existing account. But if a person still hasn&rsquo;t created a bank, then he/she needs to create a new bank account in the TyBank admin. You will be asked for the name, address, account type, and amount to deposit. Once done, the user will be given an account number and a pin number of that bank account.</li>
<li>In order to add a new account, choose the existing account option in the command. Then, input the account name and address, which should match the name of the person who wants to add a new bank account. A new account number and pin number will be generated for that new bank account (Note: the person&rsquo;s personal info such as his/her name and address are all one, even though there are more than one bank accounts)</li>
</ul>
<p>&nbsp;</p>
<p><span style="text-decoration: underline;"><strong>Database configuration:</strong></span></p>
<p>By default, we&rsquo;ve set the database to point to the free DB4 MySQL database hosting. The contents of the database can be viewed using the info (located at sqldatabase.cpp).</p>
