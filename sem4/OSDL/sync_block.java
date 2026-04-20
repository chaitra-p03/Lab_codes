class BankAccount {
    private int balance = 0;

    public void deposit(int amount) {
        if (amount <= 0) {
            System.out.println("Enter valid amount to deposit!");
            return;
        }

        synchronized (this) { 
            balance += amount;
            System.out.println(Thread.currentThread().getName() +
                    " deposited: " + amount + " | Balance: " + balance);
        }
    }

    public void withdraw(int amount) {
        synchronized (this) { 
            if (amount > balance) {
                System.out.println(Thread.currentThread().getName() +
                        " tried to withdraw " + amount + " | Insufficient balance: " + balance);
                return;
            }

            balance -= amount;
            System.out.println(Thread.currentThread().getName() +
                    " withdrew: " + amount + " | Balance: " + balance);
        }
    }
}

class DepositThread extends Thread {
    private BankAccount account;

    public DepositThread(BankAccount account) {
        this.account = account;
    }

    @Override
    public void run() {
        for (int i = 0; i < 5; i++) {
            account.deposit(100);
        }
    }
}

class WithdrawThread extends Thread {
    private BankAccount account;

    public WithdrawThread(BankAccount account) {
        this.account = account;
    }

    @Override
    public void run() {
        for (int i = 0; i < 5; i++) {
            account.withdraw(50);
        }
    }
}

public class sync_block {
    public static void main(String[] args) throws InterruptedException {
        BankAccount acc = new BankAccount();

        Thread t1 = new DepositThread(acc); 
        Thread t2 = new WithdrawThread(acc);

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        System.out.println("Final Balance operations completed.");
    }
}
